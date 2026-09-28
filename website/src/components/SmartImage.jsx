const PRODUCT_WIDTHS = [480, 800, 1100];
const WIDE_WIDTHS = [768, 1280, 1920];

function parseRatio(ratio) {
  const [w, h] = ratio.split('/').map((n) => parseFloat(n));
  return { w: w || 4, h: h || 5 };
}

/**
 * Responsive <img> wired to the responsive WebP set produced by
 * scripts/optimize-images.mjs. Reserves its aspect ratio (no CLS),
 * lazy-loads by default, and can be promoted with `eager` for LCP slots.
 */
export default function SmartImage({
  name,
  alt = '',
  variant = 'product',
  sizes = '(max-width: 760px) 94vw, 44vw',
  ratio = '4 / 5',
  eager = false,
  className = '',
  style,
}) {
  const widths = variant === 'wide' ? WIDE_WIDTHS : PRODUCT_WIDTHS;
  const { w, h } = parseRatio(ratio);
  const base = widths[widths.length - 1];

  return (
    <img
      className={`smart-img ${className}`}
      src={`/images/${name}-${base}.webp`}
      srcSet={widths.map((width) => `/images/${name}-${width}.webp ${width}w`).join(', ')}
      sizes={sizes}
      width={w * 200}
      height={h * 200}
      alt={alt}
      loading={eager ? 'eager' : 'lazy'}
      decoding={eager ? 'sync' : 'async'}
      {...(eager ? { fetchpriority: 'high' } : {})}
      style={{ aspectRatio: `${w} / ${h}`, ...style }}
    />
  );
}
