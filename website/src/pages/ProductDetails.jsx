import { useContext, useMemo } from 'react';
import { Link, Navigate, useParams } from 'react-router-dom';
import { BootContext, useOrder } from '../App.jsx';
import { gsap, useGsap, RM, splitWords, initReveals } from '../animations/gsap.js';
import { usePageMeta, useJsonLd } from '../utils/seo.js';
import products, { getProduct, CATEGORY_LABELS, formatPrice } from '../data/products.js';
import Button from '../components/Button.jsx';
import RevealImg from '../components/RevealImg.jsx';
import ProductCard from '../components/ProductCard.jsx';
import { ArrowRight, ArrowUpRight, Plus } from '../components/icons.jsx';
import '../styles/product.css';

const WHATSAPP = '201002345678';

export default function ProductDetails() {
  const { slug } = useParams();
  const product = getProduct(slug);
  const openOrder = useOrder();
  const booted = useContext(BootContext);

  const related = useMemo(() => {
    if (!product) return [];
    const sameCat = products.filter((p) => p.category === product.category && p.id !== product.id);
    const fill = products.filter((p) => p.featured && p.id !== product.id && !sameCat.includes(p));
    return [...sameCat, ...fill].slice(0, 3);
  }, [product]);

  const { prev, next } = useMemo(() => {
    if (!product) return { prev: null, next: null };
    const i = products.findIndex((p) => p.id === product.id);
    return {
      prev: products[(i - 1 + products.length) % products.length],
      next: products[(i + 1) % products.length],
    };
  }, [product]);

  const jsonLd = useMemo(() => {
    if (!product) return null;
    return {
      '@context': 'https://schema.org',
      '@type': 'Product',
      name: product.name,
      description: product.description,
      image: `/images/${product.image}-800.webp`,
      brand: { '@type': 'Brand', name: 'IBRIK' },
      offers: {
        '@type': 'Offer',
        price: product.price,
        priceCurrency: 'EGP',
        availability: 'https://schema.org/InStock',
      },
    };
  }, [product]);

  usePageMeta(
    product ? product.name : 'Pour not found',
    product ? `${product.tagline} ${product.description}` : 'This pour is not on the list.'
  );
  useJsonLd(`product-${product?.id}`, jsonLd);

  const scope = useGsap((root) => {
    initReveals(root);
    if (!booted || !product || RM) return;
    const q = gsap.utils.selector(root);
    const split = splitWords(q('.pd__name')[0]);
    gsap.timeline({ defaults: { ease: 'power4.out' } })
      .fromTo(q('.pd__crumbs'), { y: 14, autoAlpha: 0 }, { y: 0, autoAlpha: 1, duration: 0.6 }, 0.1)
      .fromTo(q('.pd__eyebrow'), { y: 16, autoAlpha: 0 }, { y: 0, autoAlpha: 1, duration: 0.6 }, 0.25)
      .fromTo(split.words, { yPercent: 118 }, { yPercent: 0, duration: 1.05, stagger: 0.07 }, 0.3)
      .fromTo(q('.pd__tag'), { y: 18, autoAlpha: 0 }, { y: 0, autoAlpha: 1, duration: 0.7 }, 0.65)
      .fromTo(q('.pd__price'), { y: 18, autoAlpha: 0 }, { y: 0, autoAlpha: 1, duration: 0.7 }, 0.75)
      .fromTo(q('.pd__desc'), { y: 22, autoAlpha: 0 }, { y: 0, autoAlpha: 1, duration: 0.8 }, 0.85)
      .fromTo(q('.pd__actions .btn'), { y: 22, autoAlpha: 0 }, { y: 0, autoAlpha: 1, duration: 0.7, stagger: 0.09 }, 0.95)
      .fromTo(q('.pd__block, .pd__nutrition'), { y: 26, autoAlpha: 0 }, { y: 0, autoAlpha: 1, duration: 0.7, stagger: 0.08 }, 1.1);
  }, [booted, slug]);

  if (!product) return <Navigate to="/menu" replace />;

  const waText = encodeURIComponent(`Hi IBRIK — I'd like to order the ${product.name}.`);

  return (
    <article ref={scope} className="pd">
      <nav className="pd__crumbs container" aria-label="Breadcrumb">
        <Link to="/menu">Menu</Link>
        <span aria-hidden="true">/</span>
        <span>{CATEGORY_LABELS[product.category]}</span>
        <span aria-hidden="true">/</span>
        <span aria-current="page" className="pd__crumbCurrent">{product.name}</span>
      </nav>

      <div className="container pd__grid">
        <div className="pd__mediaCol">
          <RevealImg
            key={product.slug}
            name={product.image}
            alt={product.alt}
            eager
            className="pd__media"
            sizes="(max-width: 900px) 94vw, 46vw"
          />
        </div>

        <div className="pd__info">
          <p className="eyebrow eyebrow--copper pd__eyebrow">
            {CATEGORY_LABELS[product.category]} · {product.serve.temp}
          </p>
          <h1 className="pd__name">{product.name}</h1>
          <p className="pd__tag">{product.tagline}</p>
          <p className="pd__price">{formatPrice(product.price)}</p>
          <p className="pd__desc">{product.description}</p>

          <div className="pd__actions">
            <Button variant="solid" arrow="right" onClick={() => openOrder(product)}>Order Now</Button>
            <Button
              variant="ghost"
              href={`https://wa.me/${WHATSAPP}?text=${waText}`}
              external
              arrow="up-right"
            >
              WhatsApp
            </Button>
          </div>

          <div className="pd__block">
            <h2 className="pd__blockTitle">Inside the cup</h2>
            <ul className="pd__ingredients">
              {product.ingredients.map((ing) => (
                <li key={ing}>
                  <span className="pd__ingIcon" aria-hidden="true"><Plus size={13} /></span>
                  {ing}
                </li>
              ))}
            </ul>
          </div>

          <div className="pd__block">
            <h2 className="pd__blockTitle">Flavor profile</h2>
            <ul className="pd__flavors">
              {product.flavor.map((f) => (
                <li key={f}>{f}</li>
              ))}
            </ul>
          </div>

          <div className="pd__block">
            <h2 className="pd__blockTitle">The build</h2>
            <dl className="pd__build">
              <div><dt>Served</dt><dd>{product.serve.temp}</dd></div>
              <div><dt>Size</dt><dd>{product.serve.volume}</dd></div>
              <div><dt>Milk</dt><dd>{product.serve.milk}</dd></div>
              <div><dt>Vessel</dt><dd>{product.serve.note}</dd></div>
            </dl>
          </div>

          <details className="pd__nutrition">
            <summary>
              Nutrition, per serve
              <span className="pd__summaryIcon" aria-hidden="true"><Plus size={14} /></span>
            </summary>
            <dl className="pd__nutritionGrid">
              <div><dt>Energy</dt><dd>{product.nutrition.kcal} kcal</dd></div>
              <div><dt>Fat</dt><dd>{product.nutrition.fat}</dd></div>
              <div><dt>Carbs</dt><dd>{product.nutrition.carbs}</dd></div>
              <div><dt>Protein</dt><dd>{product.nutrition.protein}</dd></div>
              <div><dt>Caffeine</dt><dd>{product.nutrition.caffeine}</dd></div>
            </dl>
          </details>
        </div>
      </div>

      <nav className="pd__siblings container" aria-label="Browse more pours">
        <Link to={`/products/${prev.slug}`} className="pd__sibling pd__sibling--prev">
          <span className="pd__siblingLabel">Previous pour</span>
          <span className="pd__siblingName">{prev.name}</span>
        </Link>
        <Link to={`/products/${next.slug}`} className="pd__sibling pd__sibling--next">
          <span className="pd__siblingLabel">Next pour</span>
          <span className="pd__siblingName">
            {next.name}
            <span className="lnk__arrow" aria-hidden="true"><ArrowRight size={18} /></span>
          </span>
        </Link>
      </nav>

      <section className="pd__related" aria-label="You may also like">
        <div className="container">
          <header className="section-title">
            <div className="section-title__main">
              <p className="eyebrow" data-reveal>Keep Tasting</p>
              <h2 className="section-title__heading section-title__heading--sm" data-reveal>You may also like</h2>
            </div>
            <Link to="/menu" className="lnk section-title__link" data-reveal>
              Full menu
              <span className="lnk__arrow" aria-hidden="true"><ArrowUpRight size={14} /></span>
            </Link>
          </header>
          <div className="product-grid pd__relatedGrid" data-reveal-group>
            {related.map((p) => (
              <ProductCard key={p.id} product={p} />
            ))}
          </div>
        </div>
      </section>
    </article>
  );
}
