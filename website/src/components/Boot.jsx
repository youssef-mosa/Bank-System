import { useEffect, useRef, useState } from 'react';
import { gsap, RM } from '../animations/gsap.js';

/**
 * One-time brand boot: ~1.4s max. Letters rise, a hairline sweeps, the
 * espresso curtain lifts into the hero. Skipped instantly for
 * prefers-reduced-motion. Kept deliberately short — it's a handshake,
 * not a loading screen.
 */
export default function Boot({ onDone }) {
  const ref = useRef(null);
  const [gone, setGone] = useState(false);

  useEffect(() => {
    if (RM) {
      onDone();
      setGone(true);
      return undefined;
    }
    document.body.classList.add('booting');
    const ctx = gsap.context(() => {
      const tl = gsap.timeline({
        defaults: { ease: 'power4.out' },
        onComplete: () => {
          document.body.classList.remove('booting');
          onDone();
          setGone(true);
        },
      });
      tl.fromTo(
        '.boot__letter',
        { yPercent: 112 },
        { yPercent: 0, duration: 0.85, stagger: 0.055 },
        0.05
      )
        .fromTo('.boot__sub', { autoAlpha: 0 }, { autoAlpha: 1, duration: 0.6 }, 0.7)
        .fromTo(
          '.boot__line',
          { scaleX: 0 },
          { scaleX: 1, duration: 0.85, ease: 'power2.inOut' },
          0.25
        )
        .to('.boot', { yPercent: -100, duration: 0.85, ease: 'power4.inOut' }, '+=0.18');
    }, ref);
    return () => {
      ctx.revert();
      document.body.classList.remove('booting');
    };
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, []);

  if (gone) return null;

  return (
    <div ref={ref} className="boot" aria-hidden="true">
      <div className="boot__center">
        <p className="boot__word">
          {'IBRIK'.split('').map((ch, i) => (
            <span className="sw-mask" key={i}>
              <span className="sw-word boot__letter">{ch}</span>
            </span>
          ))}
        </p>
        <span className="boot__line" />
        <p className="boot__sub">Cairo Coffee Atelier — Est. 2016</p>
      </div>
    </div>
  );
}
