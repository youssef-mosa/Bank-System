import { useContext } from 'react';
import { Link } from 'react-router-dom';
import { BootContext } from '../App.jsx';
import {
  gsap, useGsap, RM, splitWords, initReveals, parallax,
} from '../animations/gsap.js';
import { usePageMeta, useJsonLd, ORG_JSONLD } from '../utils/seo.js';
import products, { featuredProducts, CATEGORY_LABELS, formatPrice } from '../data/products.js';
import Button from '../components/Button.jsx';
import SectionTitle from '../components/SectionTitle.jsx';
import AnimatedWords from '../components/AnimatedWords.jsx';
import RevealImg from '../components/RevealImg.jsx';
import ProductCard from '../components/ProductCard.jsx';
import SmartImage from '../components/SmartImage.jsx';
import { ArrowRight } from '../components/icons.jsx';
import '../styles/home.css';

const CRAFT = [
  {
    n: '01',
    title: 'Copper & Fire',
    img: 'ibrik',
    alt: 'Hand-hammered copper ibrik with a porcelain finjan',
    text: 'Hand-hammered ibriks over open flame; beans drum-roasted eighteen kilos at a time, every batch logged by hand. Tools that reward patience, never speed.',
  },
  {
    n: '02',
    title: 'Slow Water',
    img: 'cold-brew',
    alt: 'Cold brew poured over one clear cube of ice',
    text: 'Nile-softened water, eighteen-hour cold steeps, one degree of tolerated variance. If a method needs time, we give it time. Patience you can taste.',
  },
  {
    n: '03',
    title: 'Fresh Milk',
    img: 'cortado',
    alt: 'Cortado with distinct espresso and milk layers',
    text: "Buffalo milk from small Delta farms, delivered at dawn and steamed to silk at exactly sixty degrees. Never yesterday's, never re-steamed.",
  },
  {
    n: '04',
    title: 'The Hand',
    img: 'caramel-latte',
    alt: 'Rosetta latte art with caramel drizzle',
    text: 'Sixty seconds of bloom, three wisps of steam, one steady wrist. A decade of wrist-memory in every pour — and no machine that can copy it.',
  },
];

const QUOTES = [
  {
    quote: 'The Spanish latte here ruined every other café for me. Silky, balanced, dangerously smooth.',
    name: 'Mariam S.',
    area: 'Zamalek',
  },
  {
    quote: 'You can taste the obsession. Their ibrik coffee alone is worth crossing the river for.',
    name: 'Karim E.',
    area: 'Maadi',
  },
  {
    quote: 'Elegant, calm, and the pistachio latte is a small masterpiece.',
    name: 'Salma R.',
    area: 'Alexandria',
  },
];

export default function Home() {
  usePageMeta(
    '',
    'IBRIK is a small-batch coffee atelier in Zamalek, Cairo. Rare beans roasted over copper fire, brewed slowly and poured with obsessive attention to detail.'
  );
  useJsonLd('org', ORG_JSONLD);
  const booted = useContext(BootContext);

  /* ---------- Hero entrance, plays after the boot curtain lifts ---------- */
  const heroScope = useGsap((root) => {
    if (!booted || RM) return;
    const q = gsap.utils.selector(root);
    const split = splitWords(q('.hero__title')[0]);

    const tl = gsap.timeline({ defaults: { ease: 'power4.out' } });
    tl.fromTo(
      q('.hero__frame'),
      { clipPath: 'inset(0 0 100% 0)' },
      { clipPath: 'inset(0 0 0% 0)', duration: 1.25, ease: 'power4.inOut' },
      0
    )
      .fromTo(q('.hero__frame img'), { scale: 1.24 }, { scale: 1.05, duration: 1.7, ease: 'power3.out' }, 0.15)
      .fromTo(q('.hero__eyebrow'), { y: 20, autoAlpha: 0 }, { y: 0, autoAlpha: 1, duration: 0.7 }, 0.45)
      .fromTo(split.words, { yPercent: 118 }, { yPercent: 0, duration: 1.1, stagger: 0.07 }, 0.55)
      .fromTo(q('.hero__lede'), { y: 28, autoAlpha: 0 }, { y: 0, autoAlpha: 1, duration: 0.9 }, 1.05)
      .fromTo(q('.hero__ctas .btn'), { y: 26, autoAlpha: 0 }, { y: 0, autoAlpha: 1, duration: 0.8, stagger: 0.09 }, 1.2)
      .fromTo(q('.hero__meta > span'), { y: 16, autoAlpha: 0 }, { y: 0, autoAlpha: 1, duration: 0.6, stagger: 0.08 }, 1.4)
      .fromTo(
        q('.hero__badge'),
        { scale: 0.5, autoAlpha: 0, rotation: -40 },
        { scale: 1, autoAlpha: 1, rotation: 0, duration: 1, ease: 'back.out(1.5)' },
        1.0
      )
      .fromTo(q('.hero__arabic'), { autoAlpha: 0, xPercent: 4 }, { autoAlpha: 1, xPercent: 0, duration: 1.6 }, 0.7)
      .fromTo(q('.hero__scroll'), { autoAlpha: 0 }, { autoAlpha: 1, duration: 0.8 }, 1.6);
  }, [booted]);

  /* ---------------------- Scroll-driven choreography --------------------- */
  const scope = useGsap((root) => {
    initReveals(root);
    if (RM) return;
    const q = gsap.utils.selector(root);

    // Hero drift: framed image sinks gently, arabic backdrop floats away.
    parallax(q('.hero__frame img')[0], 10, q('.hero')[0]);
    gsap.to(q('.hero__arabic'), {
      yPercent: -24,
      ease: 'none',
      scrollTrigger: { trigger: q('.hero')[0], start: 'top top', end: 'bottom top', scrub: 1 },
    });
    gsap.to(q('.hero__scroll'), {
      autoAlpha: 0,
      ease: 'none',
      scrollTrigger: { trigger: q('.hero')[0], start: '40% top', end: '55% top', scrub: true },
    });

    // Statement lines rise word by word.
    q('[data-statement-line]').forEach((line, i) => {
      const split = splitWords(line);
      gsap.fromTo(split.words, { yPercent: 118 }, {
        yPercent: 0,
        duration: 1,
        ease: 'power4.out',
        stagger: 0.05,
        delay: i * 0.09,
        scrollTrigger: { trigger: line, start: 'top 88%', once: true },
      });
    });

    // Signature moment: pinned horizontal craft chapter (desktop only,
    // reduced motion and mobile get a calm stacked layout via CSS).
    const mm = gsap.matchMedia();
    mm.add('(min-width: 1024px)', () => {
      const vp = q('.craft__viewport')[0];
      const track = q('.craft__track')[0];
      const section = q('.craft')[0];
      const dist = () => Math.max(0, track.scrollWidth - vp.clientWidth);

      gsap.to(track, {
        x: () => -dist(),
        ease: 'none',
        scrollTrigger: {
          trigger: section,
          start: 'top top',
          end: () => `+=${dist()}`,
          pin: true,
          scrub: 0.6,
          anticipatePin: 1,
          invalidateOnRefresh: true,
          onUpdate: (self) => {
            gsap.set(q('.craft__progressBar'), { scaleX: self.progress });
          },
        },
      });
    });
  });

  return (
    <div ref={(node) => { scope.current = node; heroScope.current = node; }}>
      {/* ============================ HERO ============================ */}
      <section className="hero" aria-label="Introduction">
        <span className="hero__arabic" lang="ar" aria-hidden="true">قهوة</span>
        <div className="container hero__inner">
          <div className="hero__content">
            <p className="eyebrow hero__eyebrow">Cairo Coffee Atelier — Est. 2016</p>
            <h1 className="hero__title">The quiet art of qahwa.</h1>
            <p className="hero__lede">
              Small-batch beans roasted over copper fire in Zamalek — brewed slowly,
              poured deliberately, and served like it matters. Because it does.
            </p>
            <div className="hero__ctas">
              <Button to="/menu" variant="solid" arrow="right">Explore the Menu</Button>
              <Button to="/about" variant="ghost" arrow="right">Our Story</Button>
            </div>
            <div className="hero__meta" aria-label="At a glance">
              <span>18 kg micro-roasts</span>
              <span>03 single origins</span>
              <span>12 seats, one slow bar</span>
            </div>
          </div>

          <div className="hero__visual">
            <figure className="hero__frame">
              <SmartImage
                name="ibrik"
                alt="Hand-hammered copper ibrik beside a porcelain finjan of Turkish coffee — the IBRIK signature serve"
                sizes="(max-width: 900px) 88vw, 40vw"
                eager
              />
            </figure>
            <div className="hero__badge" aria-hidden="true">
              <svg viewBox="0 0 120 120" className="hero__badgeSpin">
                <defs>
                  <path id="badge-circle" d="M60,60 m-44,0 a44,44 0 1,1 88,0 a44,44 0 1,1 -88,0" />
                </defs>
                <text>
                  <textPath href="#badge-circle">Slow roasted · Zamalek · Small batch · Since 2016 ·</textPath>
                </text>
              </svg>
              <span className="hero__badgeDot" />
            </div>
          </div>
        </div>
        <a className="hero__scroll" href="#statement">
          <span>Scroll</span>
          <span className="hero__scrollLine" aria-hidden="true" />
        </a>
      </section>

      {/* ========================= STATEMENT ========================== */}
      <section id="statement" className="statement panel--dark" aria-label="Brand statement">
        <div className="container statement__inner">
          <p className="eyebrow eyebrow--copper" data-reveal>The Atelier</p>
          <h2 className="statement__lines">
            <span className="statement__line" data-statement-line>More than coffee,</span>
            <span className="statement__line statement__line--accent" data-statement-line>it's the pause</span>
            <span className="statement__line" data-statement-line>between moments.</span>
          </h2>
          <p className="statement__copy" data-reveal>
            IBRIK began with a copper pot and an unreasonable standard. A decade later,
            that standard hasn't moved an inch — every bean cupped blind, every roast
            logged by hand, every cup poured like it was the first.
          </p>
          <dl className="stats" data-reveal-group>
            <div className="stats__item">
              <dt>Established</dt>
              <dd>2016</dd>
            </div>
            <div className="stats__item">
              <dt>Single origins</dt>
              <dd>03</dd>
            </div>
            <div className="stats__item">
              <dt>Roast batch</dt>
              <dd>18 kg</dd>
            </div>
            <div className="stats__item">
              <dt>Water at</dt>
              <dd>93°C</dd>
            </div>
          </dl>
        </div>
      </section>

      {/* ======================== FEATURED POURS ======================= */}
      <section className="featured" aria-label="Featured products">
        <div className="container">
          <SectionTitle eyebrow="The Pours" title="Six ways to slow down." linkTo="/menu" linkLabel="Full menu" />
          <div className="product-grid featured__grid" data-reveal-group>
            {featuredProducts.map((p) => (
              <ProductCard key={p.id} product={p} />
            ))}
          </div>
        </div>
      </section>

      {/* ========================= STORY TEASER ======================== */}
      <section className="story-teaser panel--sand" aria-label="Our story">
        <div className="container story-teaser__grid">
          <RevealImg
            name="flat-white"
            alt="A date and honey flat white with tulip latte art, served with Medjool dates"
            className="story-teaser__img"
            drift={6}
          />
          <div className="story-teaser__content">
            <p className="eyebrow" data-reveal>Our Story</p>
            <AnimatedWords as="h2" text="Where every cup begins." className="story-teaser__title" />
            <p data-reveal>
              A copper cezve on a Khan el-Khalili cart. A grandson who never forgot
              the smell of it. IBRIK is what happens when heritage refuses to stay
              in the past.
            </p>
            <p data-reveal>
              In 2016 we opened a nine-seat bar in Zamalek and began roasting in
              eighteen-kilo batches. We still turn down beans we'd rather drink
              than sell.
            </p>
            <div data-reveal>
              <Button to="/about" variant="ghost" arrow="right">Read our story</Button>
            </div>
          </div>
        </div>
      </section>

      {/* ===================== CRAFT — PINNED CHAPTER ==================== */}
      <section className="craft panel--dark" aria-label="The craft">
        <div className="container craft__head">
          <div>
            <p className="eyebrow eyebrow--copper" data-reveal>The Craft</p>
            <AnimatedWords as="h2" text="Obsessed, in four acts." className="craft__title" />
          </div>
          <p className="craft__note" data-reveal>
            What goes into the cup — and, more importantly, what never does.
          </p>
        </div>
        <div className="craft__viewport">
          <div className="craft__track">
            {CRAFT.map((c) => (
              <article className="craft-panel" key={c.n}>
                <div className="craft-panel__top">
                  <span className="craft-panel__index">{c.n}</span>
                  <span className="craft-panel__rule" aria-hidden="true" />
                </div>
                <h3 className="craft-panel__title">{c.title}</h3>
                <p className="craft-panel__text">{c.text}</p>
                <figure className="craft-panel__media">
                  <SmartImage name={c.img} alt={c.alt} sizes="(max-width: 1023px) 80vw, 22vw" />
                </figure>
              </article>
            ))}
          </div>
          <div className="craft__progress" aria-hidden="true">
            <span className="craft__progressBar" />
          </div>
        </div>
      </section>

      {/* =========================== THE INDEX ========================== */}
      <section className="index" aria-label="Full product index">
        <div className="container">
          <SectionTitle eyebrow="The Index" title="Tonight's pour list." linkTo="/menu" linkLabel="Browse the menu" />
          <ul className="index__list" data-reveal-group>
            {products.map((p) => (
              <li key={p.id}>
                <Link className="index__row" to={`/products/${p.slug}`}>
                  <span className="index__name">{p.name}</span>
                  <span className="index__cat">{CATEGORY_LABELS[p.category]}</span>
                  <span className="index__price">{formatPrice(p.price)}</span>
                  <span className="index__arrow" aria-hidden="true"><ArrowRight size={16} /></span>
                </Link>
              </li>
            ))}
          </ul>
        </div>
      </section>

      {/* ========================== TESTIMONIALS ======================== */}
      <section className="quotes panel--sand" aria-label="Testimonials">
        <div className="container">
          <SectionTitle eyebrow="Kind Words" title="Poured, sipped, repeated." />
          <div className="quotes__grid" data-reveal-group>
            {QUOTES.map((qt) => (
              <figure className="quote" key={qt.name}>
                <blockquote className="quote__text">“{qt.quote}”</blockquote>
                <figcaption className="quote__by">
                  <span className="quote__name">{qt.name}</span>
                  <span className="quote__area">{qt.area}</span>
                </figcaption>
              </figure>
            ))}
          </div>
        </div>
      </section>

      {/* =========================== FINAL CTA ========================== */}
      <section className="finalcta panel--dark" aria-label="Visit us">
        <div className="container finalcta__grid">
          <div className="finalcta__content">
            <p className="eyebrow eyebrow--copper" data-reveal>One Last Thing</p>
            <AnimatedWords as="h2" text="Your next favorite cup is waiting." className="finalcta__title" />
            <p className="finalcta__lede" data-reveal>
              Twelve seats, one slow bar, and a kettle that's never off.
            </p>
            <div className="finalcta__ctas" data-reveal>
              <Button to="/menu" variant="cream" arrow="right">Explore the Menu</Button>
              <Button to="/about" variant="ghost" arrow="right">Our Story</Button>
            </div>
          </div>
          <RevealImg
            name="spanish-latte"
            alt="A Spanish latte layered over clear ice — condensed milk beneath a double shot"
            className="finalcta__img finalcta__img--arch"
            drift={7}
          />
        </div>
      </section>
    </div>
  );
}
