import { Link } from 'react-router-dom';
import { ArrowRight, ArrowUpRight } from './icons.jsx';

/**
 * Brand button. Renders a router Link, an anchor, or a <button> depending
 * on props. Variants: solid | ghost | line (underline only). Tones adapt
 * to light/dark sections via .btn--onDark on a parent.
 */
export default function Button({
  to,
  href,
  external = false,
  onClick,
  type = 'button',
  variant = 'solid',
  size,
  arrow = 'none', // 'right' | 'up-right' | 'none'
  className = '',
  children,
  ...rest
}) {
  const cls = [
    'btn',
    `btn--${variant}`,
    size ? `btn--${size}` : '',
    arrow !== 'none' ? 'btn--hasArrow' : '',
    className,
  ]
    .filter(Boolean)
    .join(' ');

  const content = (
    <>
      <span className="btn__label">{children}</span>
      {arrow !== 'none' && (
        <span className="btn__arrow" aria-hidden="true">
          {arrow === 'up-right' ? <ArrowUpRight size={15} /> : <ArrowRight size={15} />}
        </span>
      )}
    </>
  );

  if (to) {
    return (
      <Link to={to} className={cls} onClick={onClick} {...rest}>
        {content}
      </Link>
    );
  }
  if (href) {
    return (
      <a
        href={href}
        className={cls}
        onClick={onClick}
        {...(external ? { target: '_blank', rel: 'noopener noreferrer' } : {})}
        {...rest}
      >
        {content}
      </a>
    );
  }
  return (
    <button type={type} className={cls} onClick={onClick} {...rest}>
      {content}
    </button>
  );
}
