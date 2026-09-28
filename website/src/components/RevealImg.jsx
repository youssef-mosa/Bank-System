import SmartImage from './SmartImage.jsx';
import { gsap, useGsap, RM, parallax } from '../animations/gsap.js';

/**
 * Framed editorial image: clip-path wipe + inner settle-scale on enter,
 * optional scroll parallax drift. Transform/clip only — GPU friendly.
 */
export default function RevealImg({
  name,
  alt,
  variant,
  sizes,
  ratio,
  eager = false,
  drift = 0, // yPercent parallax amount, 0 = off
  className = '',
  frame = true,
}) {
  const scope = useGsap((root) => {
    const img = root.querySelector('img');
    if (!RM) {
      const tl = gsap.timeline({
        scrollTrigger: { trigger: root, start: 'top 86%', once: true },
      });
      tl.fromTo(
        root,
        { clipPath: 'inset(16% 10% 16% 10%)' },
        { clipPath: 'inset(0% 0% 0% 0%)', duration: 1.25, ease: 'power4.inOut' }
      ).fromTo(
        img,
        { scale: 1.22 },
        { scale: 1.04, duration: 1.55, ease: 'power3.out' },
        0
      );
    }
    if (drift) parallax(img, drift, root);
  }, []);

  return (
    <figure ref={scope} className={`reveal-img ${frame ? 'reveal-img--framed' : ''} ${className}`}>
      <SmartImage name={name} alt={alt} variant={variant} sizes={sizes} ratio={ratio} eager={eager} />
    </figure>
  );
}
