import { useEffect, useRef, useState } from 'react';
import { Link, NavLink, useLocation } from 'react-router-dom';
import { gsap, RM } from '../animations/gsap.js';
import { useOrder } from '../App.jsx';

const LINKS = [
  { to: '/menu', label: 'Menu' },
  { to: '/about', label: 'Our Story' },
  { to: '/contact', label: 'Contact' },
];

export default function Navbar() {
  const [scrolled, setScrolled] = useState(false);
  const [open, setOpen] = useState(false);
  const overlayRef = useRef(null);
  const toggleRef = useRef(null);
  const location = useLocation();
  const openOrder = useOrder();

  // Compress + backdrop when leaving the hero zone.
  useEffect(() => {
    let ticking = false;
    const onScroll = () => {
      if (ticking) return;
      ticking = true;
      requestAnimationFrame(() => {
        setScrolled(window.scrollY > 48);
        ticking = false;
      });
    };
    onScroll();
    window.addEventListener('scroll', onScroll, { passive: true });
    return () => window.removeEventListener('scroll', onScroll);
  }, []);

  // Close the mobile menu on navigation.
  useEffect(() => setOpen(false), [location.pathname]);

  // Lock scroll + choreograph the overlay content.
  // The curtain itself (clip-path wipe open AND close) is a pure CSS
  // transition on .site-nav--open — GSAP only staggers the links in.
  useEffect(() => {
    document.body.classList.toggle('nav-open', open);
    if (!open) {
      if (overlayRef.current?.contains(document.activeElement)) {
        toggleRef.current?.focus({ preventScroll: true });
      }
      return () => document.body.classList.remove('nav-open');
    }
    const overlay = overlayRef.current;
    if (overlay && !RM) {
      const links = overlay.querySelectorAll(
        '.mobile-menu__link, .mobile-menu__order, .mobile-menu__meta > *'
      );
      gsap.fromTo(
        links,
        { y: 44, autoAlpha: 0 },
        { y: 0, autoAlpha: 1, duration: 0.7, ease: 'power3.out', stagger: 0.06, delay: 0.28 }
      );
    }
    overlay?.querySelector('.mobile-menu__link')?.focus({ preventScroll: true });
    const onKey = (e) => {
      if (e.key === 'Escape') setOpen(false);
    };
    window.addEventListener('keydown', onKey);
    return () => {
      window.removeEventListener('keydown', onKey);
      document.body.classList.remove('nav-open');
    };
  }, [open]);

  return (
    <header className={`site-nav ${scrolled || open ? 'site-nav--solid' : ''} ${open ? 'site-nav--open' : ''}`}>
      <div className="site-nav__inner">
        <Link to="/" className="brand" aria-label="IBRIK — home">
          <span className="brand__word">IBRIK</span>
          <span className="brand__sub">Cairo Coffee Atelier</span>
        </Link>

        <nav className="site-nav__links" aria-label="Primary">
          {LINKS.map((l) => (
            <NavLink key={l.to} to={l.to} className="nav-lnk">
              {l.label}
            </NavLink>
          ))}
        </nav>

        <div className="site-nav__actions">
          <button
            type="button"
            className="btn btn--solid btn--sm btn--hasArrow site-nav__order"
            onClick={() => openOrder()}
          >
            <span className="btn__label">Order Now</span>
            <span className="btn__arrow" aria-hidden="true">
              <svg width="14" height="14" viewBox="0 0 24 24" fill="none" aria-hidden="true">
                <path d="M4 12h15M13 5l7 7-7 7" stroke="currentColor" strokeWidth="1.8" strokeLinecap="round" strokeLinejoin="round" />
              </svg>
            </span>
          </button>
          <button
            ref={toggleRef}
            type="button"
            className={`nav-toggle ${open ? 'nav-toggle--open' : ''}`}
            aria-expanded={open}
            aria-controls="mobile-menu"
            aria-label={open ? 'Close menu' : 'Open menu'}
            onClick={() => setOpen((v) => !v)}
          >
            <span className="nav-toggle__line" />
            <span className="nav-toggle__line" />
          </button>
        </div>
      </div>

      <div
        ref={overlayRef}
        id="mobile-menu"
        className="mobile-menu"
        aria-hidden={!open}
      >
        <nav className="mobile-menu__nav" aria-label="Mobile">
          <Link to="/" className="mobile-menu__link" tabIndex={open ? 0 : -1}>
            Home
          </Link>
          {LINKS.map((l) => (
            <Link key={l.to} to={l.to} className="mobile-menu__link" tabIndex={open ? 0 : -1}>
              {l.label}
            </Link>
          ))}
          <button
            type="button"
            className="btn btn--cream mobile-menu__order"
            tabIndex={open ? 0 : -1}
            onClick={() => {
              setOpen(false);
              openOrder();
            }}
          >
            <span className="btn__label">Order Now</span>
          </button>
        </nav>
        <div className="mobile-menu__meta">
          <p>12 Bahgat Ali St, Zamalek, Cairo</p>
          <p>Sun–Thu 7:00–23:00 · Fri–Sat 8:00–00:00</p>
          <p className="mobile-menu__arabic" lang="ar" aria-hidden="true">قهوة</p>
        </div>
      </div>
    </header>
  );
}
