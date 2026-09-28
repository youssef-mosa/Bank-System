import { useContext, useLayoutEffect, useMemo, useRef, useState } from 'react';
import { BootContext } from '../App.jsx';
import { gsap, Flip, useGsap, RM, splitWords, initReveals } from '../animations/gsap.js';
import { usePageMeta } from '../utils/seo.js';
import products, { CATEGORIES } from '../data/products.js';
import ProductCard from '../components/ProductCard.jsx';
import '../styles/menu.css';

export default function Menu() {
  usePageMeta(
    'The Menu',
    'The full IBRIK pour list — signature espresso, Turkish ibrik, iced pours and specialty lattes, roasted and brewed in Zamalek, Cairo.'
  );
  const booted = useContext(BootContext);
  const [cat, setCat] = useState('all');
  const flipState = useRef(null);
  const gridRef = useRef(null);

  const visible = useMemo(
    () => (cat === 'all' ? products : products.filter((p) => p.category === cat)),
    [cat]
  );

  /* Head entrance + initial card reveal */
  const scope = useGsap((root) => {
    initReveals(root);
    if (!booted || RM) return;
    const q = gsap.utils.selector(root);
    const split = splitWords(q('.page-head__title')[0]);
    gsap.timeline({ defaults: { ease: 'power4.out' } })
      .fromTo(q('.page-head__eyebrow'), { y: 18, autoAlpha: 0 }, { y: 0, autoAlpha: 1, duration: 0.7 }, 0.1)
      .fromTo(split.words, { yPercent: 118 }, { yPercent: 0, duration: 1.05, stagger: 0.07 }, 0.2)
      .fromTo(q('.page-head__lede'), { y: 24, autoAlpha: 0 }, { y: 0, autoAlpha: 1, duration: 0.85 }, 0.55)
      .fromTo(q('.menu-filter'), { y: 20, autoAlpha: 0 }, { y: 0, autoAlpha: 1, duration: 0.7 }, 0.75)
      .fromTo(
        q('.menu-page__grid .product-card'),
        { y: 44, autoAlpha: 0 },
        { y: 0, autoAlpha: 1, duration: 0.85, stagger: 0.055, ease: 'power3.out', clearProps: 'transform' },
        0.9
      );
  }, [booted]);

  /* Record card positions before the category swap (GSAP Flip). */
  const changeCategory = (id) => {
    if (id === cat) return;
    if (!RM) flipState.current = Flip.getState('[data-flip-id]');
    setCat(id);
  };

  /* Animate the layout change: re-flow existing cards, fade new ones in. */
  useLayoutEffect(() => {
    if (!flipState.current) return;
    const state = flipState.current;
    flipState.current = null;
    const ctx = gsap.context(() => {
      Flip.from(state, {
        duration: 0.6,
        ease: 'power3.inOut',
        absolute: true,
        scale: true,
        stagger: 0.03,
        onEnter: (els) =>
          gsap.fromTo(
            els,
            { autoAlpha: 0, y: 42, scale: 0.95 },
            { autoAlpha: 1, y: 0, scale: 1, duration: 0.65, ease: 'power3.out', stagger: 0.06, delay: 0.1 }
          ),
        onLeave: (els) =>
          gsap.to(els, { autoAlpha: 0, scale: 0.95, y: -14, duration: 0.28, ease: 'power2.in' }),
      });
    }, gridRef);
    return () => ctx.revert();
  }, [visible]);

  return (
    <div ref={scope} className="menu-page">
      <header className="page-head">
        <div className="container">
          <p className="eyebrow page-head__eyebrow">The Pour List — Season 10</p>
          <h1 className="page-head__title">The Menu.</h1>
          <p className="page-head__lede">
            Ten pours, no filler. Everything below is roasted in eighteen-kilo batches
            and made to order — the list turns with the seasons, the standard doesn't.
          </p>
        </div>
      </header>

      <div className="menu-filter__bar">
        <div className="container">
          <div className="menu-filter" role="group" aria-label="Filter by category">
            {CATEGORIES.map((c) => (
              <button
                key={c.id}
                type="button"
                className={`menu-filter__btn ${cat === c.id ? 'is-active' : ''}`}
                aria-pressed={cat === c.id}
                onClick={() => changeCategory(c.id)}
              >
                {c.label}
              </button>
            ))}
          </div>
        </div>
      </div>

      <section className="container menu-page__gridWrap" aria-label="Products">
        <p className="menu-page__count" role="status">
          {visible.length} {visible.length === 1 ? 'pour' : 'pours'}
          {cat !== 'all' && ` in ${CATEGORIES.find((c) => c.id === cat)?.label}`}
        </p>
        <div ref={gridRef} className="product-grid menu-page__grid">
          {visible.map((p) => (
            <ProductCard key={p.id} product={p} />
          ))}
        </div>
      </section>
    </div>
  );
}
