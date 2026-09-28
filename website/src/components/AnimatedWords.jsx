import { useRef } from 'react';
import { gsap, splitWords, RM } from '../animations/gsap.js';
import { useLayoutEffect } from 'react';

/**
 * Heading/paragraph whose words rise from behind an overflow mask when
 * scrolled into view. Words are aria-hidden; the original phrase remains
 * accessible via aria-label.
 */
export default function AnimatedWords({
  as: Tag = 'span',
  text,
  className = '',
  delay = 0,
  start = 'top 88%',
}) {
  const ref = useRef(null);

  useLayoutEffect(() => {
    const el = ref.current;
    if (!el || RM) return undefined;
    const split = splitWords(el);
    const ctx = gsap.context(() => {
      gsap.fromTo(
        split.words,
        { yPercent: 118 },
        {
          yPercent: 0,
          duration: 1.05,
          ease: 'power4.out',
          stagger: 0.055,
          delay,
          scrollTrigger: { trigger: el, start, once: true },
        }
      );
    }, el);
    return () => {
      ctx.revert();
      split.restore();
    };
  }, [text, delay, start]);

  return (
    <Tag ref={ref} className={`words-reveal ${className}`}>
      {text}
    </Tag>
  );
}
