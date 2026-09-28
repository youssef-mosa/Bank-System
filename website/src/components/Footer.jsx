import { Link } from 'react-router-dom';
import { ArrowUpRight } from './icons.jsx';
import { useOrder } from '../App.jsx';

const SOCIALS = [
  { label: 'Instagram', href: 'https://instagram.com' },
  { label: 'TikTok', href: 'https://tiktok.com' },
  { label: 'Facebook', href: 'https://facebook.com' },
];

export default function Footer() {
  const openOrder = useOrder();
  return (
    <footer className="site-footer">
      <div className="container">
        <div className="site-footer__grid">
          <div className="site-footer__brand">
            <p className="brand__word brand__word--footer">IBRIK</p>
            <p className="site-footer__blurb">
              A small-batch coffee atelier in Zamalek. Rare beans, copper fire,
              and ten years of quiet obsession in every cup.
            </p>
            <button type="button" className="btn btn--cream btn--sm btn--hasArrow" onClick={() => openOrder()}>
              <span className="btn__label">Order Now</span>
              <span className="btn__arrow" aria-hidden="true"><ArrowUpRight size={14} /></span>
            </button>
          </div>

          <nav className="site-footer__col" aria-label="Explore">
            <h3 className="site-footer__head">Explore</h3>
            <Link to="/menu">Menu</Link>
            <Link to="/about">Our Story</Link>
            <Link to="/contact">Contact</Link>
          </nav>

          <div className="site-footer__col">
            <h3 className="site-footer__head">Visit</h3>
            <p>12 Bahgat Ali Street<br />Zamalek, Cairo</p>
            <p>Sun–Thu · 7:00–23:00<br />Fri–Sat · 8:00–00:00</p>
          </div>

          <div className="site-footer__col" aria-label="Follow">
            <h3 className="site-footer__head">Follow</h3>
            {SOCIALS.map((s) => (
              <a key={s.label} href={s.href} target="_blank" rel="noopener noreferrer" className="site-footer__social">
                {s.label}
                <span className="lnk__arrow" aria-hidden="true"><ArrowUpRight size={13} /></span>
              </a>
            ))}
            <a href="mailto:hello@ibrik.coffee" className="site-footer__social">
              hello@ibrik.coffee
              <span className="lnk__arrow" aria-hidden="true"><ArrowUpRight size={13} /></span>
            </a>
          </div>
        </div>

        <div className="site-footer__bottom">
          <p>© {new Date().getFullYear()} IBRIK Coffee Atelier. Crafted slowly in Cairo.</p>
          <p className="site-footer__note" lang="ar">الإبريق — فن القهوة الهادئ</p>
        </div>
      </div>
      <p className="site-footer__word" aria-hidden="true">IBRIK</p>
    </footer>
  );
}
