import { useLayoutEffect, useRef } from 'react';
import gsap from 'gsap';
import { ScrollTrigger } from 'gsap/ScrollTrigger';
import { Flip } from 'gsap/Flip';

gsap.registerPlugin(ScrollTrigger, Flip);
gsap.defaults({ ease: 'power3.out' });

export { gsap, ScrollTrigger, Flip };

/** User asked the OS for reduced motion — every animation entry point checks this. */
export const RM =
  typeof window !== 'undefined' &&
  window.matchMedia('(prefers-reduced-motion: reduce)').matches;

if (RM && typeof document !== 'undefined') {
  document.documentElement.classList.add('reduced-motion');
}

/**
 * gsap.context + useLayoutEffect wrapper. Every animation in the app runs
 * through this so it's scoped and fully reverted when the component unmounts.
 */
export function useGsap(callback, deps = []) {
  const scope = useRef(null);
  useLayoutEffect(() => {
    const ctx = gsap.context(() => callback(scope.current), scope);
    return () => ctx.revert();
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, deps);
  return scope;
}

/**
 * Splits an element's text into masked word spans for staggered reveals.
 * Returns an restore() function. Cheap SplitText alternative — words only,
 * which is all the design needs (avoids re-splitting on resize).
 */
export function splitWords(el) {
  const original = el.textContent;
  const words = original.trim().split(/\s+/);
  el.setAttribute('aria-label', original.trim());
  el.textContent = '';
  const inners = [];
  words.forEach((word, i) => {
    const mask = document.createElement('span');
    mask.className = 'sw-mask';
    mask.setAttribute('aria-hidden', 'true');
    const inner = document.createElement('span');
    inner.className = 'sw-word';
    inner.textContent = word;
    mask.appendChild(inner);
    el.appendChild(mask);
    if (i < words.length - 1) el.appendChild(document.createTextNode(' '));
    inners.push(inner);
  });
  return {
    words: inners,
    restore() {
      el.removeAttribute('aria-label');
      el.textContent = original;
    },
  };
}

/**
 * Attaches scroll-triggered reveals for [data-reveal] (single element,
 * y-fade) and [data-reveal-group] > * (staggered children) inside `scopeEl`.
 * Honors reduced motion by leaving everything fully visible.
 */
export function initReveals(scopeEl) {
  if (RM) return; // No initial hidden states are applied — content stays fully visible.

  const singles = gsap.utils.toArray('[data-reveal]', scopeEl);
  const groups = gsap.utils.toArray('[data-reveal-group]', scopeEl);

  singles.forEach((el) => {
    gsap.fromTo(
      el,
      { y: 36, autoAlpha: 0 },
      {
        y: 0,
        autoAlpha: 1,
        duration: 1,
        ease: 'power3.out',
        scrollTrigger: { trigger: el, start: 'top 88%', once: true },
      }
    );
  });

  groups.forEach((group) => {
    const items = group.children;
    gsap.fromTo(
      items,
      { y: 44, autoAlpha: 0 },
      {
        y: 0,
        autoAlpha: 1,
        duration: 0.9,
        ease: 'power3.out',
        stagger: 0.12,
        scrollTrigger: { trigger: group, start: 'top 84%', once: true },
      }
    );
  });
}

/**
 * Scroll-driven scale-down for framed images (1.08 → 1). Transform-only.
 */
export function scaleOnScroll(img, triggerEl) {
  if (RM || !img) return;
  gsap.fromTo(
    img,
    { scale: 1.08 },
    {
      scale: 1,
      ease: 'none',
      scrollTrigger: { trigger: triggerEl, start: 'top bottom', end: 'bottom top', scrub: 0.6 },
    }
  );
}

/** Gentle parallax drift (translateY percentage scrub). */
export function parallax(el, amount = 8, triggerEl = null) {
  if (RM || !el) return;
  gsap.fromTo(
    el,
    { yPercent: -Math.abs(amount) / 2 },
    {
      yPercent: Math.abs(amount) / 2,
      ease: 'none',
      scrollTrigger: {
        trigger: triggerEl ?? el,
        start: 'top bottom',
        end: 'bottom top',
        scrub: 0.7,
      },
    }
  );
}
