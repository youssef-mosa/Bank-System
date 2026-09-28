import { Link } from 'react-router-dom';
import AnimatedWords from './AnimatedWords.jsx';
import { ArrowRight } from './icons.jsx';

/**
 * Editorial section header: copper eyebrow + large serif heading with a
 * masked word reveal, optional "view all" link on the right.
 */
export default function SectionTitle({ eyebrow, title, linkTo, linkLabel, align = 'left', className = '' }) {
  return (
    <header className={`section-title section-title--${align} ${className}`}>
      <div className="section-title__main">
        {eyebrow && (
          <p className="eyebrow" data-reveal>
            {eyebrow}
          </p>
        )}
        <AnimatedWords as="h2" text={title} className="section-title__heading" />
      </div>
      {linkTo && (
        <Link to={linkTo} className="lnk section-title__link" data-reveal>
          {linkLabel}
          <span className="lnk__arrow" aria-hidden="true">
            <ArrowRight size={14} />
          </span>
        </Link>
      )}
    </header>
  );
}
