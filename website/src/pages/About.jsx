import { useContext } from 'react';
import { Link } from 'react-router-dom';
import { BootContext } from '../App.jsx';
import { gsap, useGsap, RM, splitWords, initReveals } from '../animations/gsap.js';
import { usePageMeta } from '../utils/seo.js';
import Button from '../components/Button.jsx';
import AnimatedWords from '../components/AnimatedWords.jsx';
import RevealImg from '../components/RevealImg.jsx';
import { ArrowRight } from '../components/icons.jsx';
import '../styles/about.css';

const TIMELINE = [
  {
    year: '2016',
    title: 'A nine-seat bar in Zamalek',
    text: "Omar El-Amin leaves a finance career, buys a secondhand 18-kilo roaster, and opens a bar with nine seats and one rule: nothing poured that we wouldn't drink twice.",
  },
  {
    year: '2019',
    title: 'The single-origin program',
    text: 'First direct relationships with growers in Haraz (Yemen), Guji (Ethiopia) and Huila (Colombia). Every lot is now cupped blind three times before it earns a place on the shelf.',
  },
  {
    year: '2022',
    title: 'The Atelier opens',
    text: 'The bar doubles into a cupping room and slow bar. Copper ibriks return to the counter — heritage brewing, treated with the same precision as the espresso program.',
  },
  {
    year: '2026',
    title: 'Ten years, same standard',
    text: 'Still roasting in eighteen-kilo batches. Still twelve seats. Still turning down beans we would rather drink than sell.',
  },
];

const VALUES = [
  {
    n: '01',
    title: 'Obsession over trends',
    text: 'No seasonal gimmicks. The menu turns when the harvest does — not when the algorithm says so.',
  },
  {
    n: '02',
    title: 'Heritage, engineered',
    text: 'The ibrik our grandfather used is on the counter every morning, held to lab-grade tolerances.',
  },
  {
    n: '03',
    title: 'Radical freshness',
    text: 'Milk arrives at dawn. Beans rest exactly nine days post-roast. Cold brew steeps eighteen hours — never seventeen.',
  },
  {
    n: '04',
    title: 'Cairo, first',
    text: 'Dates from Siwa, honey from the Delta, cups thrown by a workshop in Fustat. This city built us; we pour for it.',
  },
];

export default function About() {
  usePageMeta(
    'Our Story',
    'From a copper cezve on a Khan el-Khalili cart to a Zamalek coffee atelier — the ten-year story of IBRIK, Cairo.'
  );
  const booted = useContext(BootContext);

  const scope = useGsap((root) => {
    initReveals(root);
    if (!booted || RM) return;
    const q = gsap.utils.selector(root);
    const split = splitWords(q('.page-head__title')[0]);
    gsap.timeline({ defaults: { ease: 'power4.out' } })
      .fromTo(q('.page-head__eyebrow'), { y: 18, autoAlpha: 0 }, { y: 0, autoAlpha: 1, duration: 0.7 }, 0.1)
      .fromTo(split.words, { yPercent: 118 }, { yPercent: 0, duration: 1.05, stagger: 0.07 }, 0.2)
      .fromTo(q('.page-head__lede'), { y: 24, autoAlpha: 0 }, { y: 0, autoAlpha: 1, duration: 0.85 }, 0.55);
  }, [booted]);

  return (
    <div ref={scope} className="about">
      <header className="page-head page-head--tall">
        <div className="container">
          <p className="eyebrow page-head__eyebrow">Our Story</p>
          <h1 className="page-head__title">Where every cup begins.</h1>
          <p className="page-head__lede">
            IBRIK is a small-batch coffee atelier on the banks of the Nile — part
            laboratory, part living room, and entirely in love with the slow side
            of coffee.
          </p>
        </div>
      </header>

      <section className="about__heroImg container" aria-label="Inside the atelier">
        <RevealImg
          name="caramel-latte"
          alt="A caramel latte with rosetta art resting on a cafe table at IBRIK, Zamalek"
          variant="product"
          sizes="(max-width: 900px) 94vw, 76vw"
          ratio="16 / 9"
          drift={5}
        />
        <p className="about__caption" data-reveal>
          The atelier, early morning — first roasts cooling, first ibrik on the flame.
        </p>
      </section>

      <section className="about__story container" aria-label="The beginning">
        <div className="about__storySticky">
          <p className="eyebrow" data-reveal>The Beginning</p>
          <AnimatedWords as="h2" text="It started with a copper pot." className="about__storyTitle" />
        </div>
        <div className="about__storyBody">
          <p data-reveal>
            In the 1960s, Omar El-Amin's grandfather pushed a coffee cart through
            Khan el-Khalili, pouring Turkish coffee from a hand-hammered copper
            cezve for merchants who had nowhere to sit and no reason to hurry.
            He believed a cup of coffee was a contract: I give you my attention,
            you give me three minutes of stillness.
          </p>
          <p data-reveal>
            Fifty years later, Omar found the cezve in a cardboard box, polished
            it with lemon and salt, and spent a year learning why his grandfather's
            coffee tasted the way it did. The answer was never the beans — it was
            the patience. The cezve sits on our counter today, next to a
            seventy-kilo espresso machine that gets used a lot less than you'd think.
          </p>
          <p data-reveal>
            That tension — heritage on one side, precision on the other — is the
            whole brand. We cup blind and log every roast by hand. We weigh milk
            to the gram and still judge ibrik foam by eye. One foot in Khan
            el-Khalili, one foot in the future. Exactly where we intend to stay.
          </p>
          <div className="about__sign" data-reveal>
            <p className="about__signName">Omar El-Amin</p>
            <p className="about__signRole">Founder &amp; head roaster</p>
          </div>
        </div>
      </section>

      <section className="about__duo container" aria-label="The counter">
        <RevealImg name="cortado" alt="A cortado on the counter at the IBRIK atelier" className="about__duoImg about__duoImg--a" drift={4} />
        <RevealImg name="pistachio-latte" alt="A pistachio latte crowned with crushed kernels" className="about__duoImg about__duoImg--b" drift={-4} />
      </section>

      <section className="about__timeline panel--dark" aria-label="Milestones">
        <div className="container">
          <p className="eyebrow eyebrow--copper" data-reveal>A Decade in Four Chapters</p>
          <AnimatedWords as="h2" text="Slow, on purpose." className="about__timelineTitle" />
          <ol className="tl" data-reveal-group>
            {TIMELINE.map((t) => (
              <li className="tl__item" key={t.year}>
                <span className="tl__year">{t.year}</span>
                <div className="tl__body">
                  <h3>{t.title}</h3>
                  <p>{t.text}</p>
                </div>
              </li>
            ))}
          </ol>
        </div>
      </section>

      <section className="about__values" aria-label="What we believe">
        <div className="container">
          <p className="eyebrow" data-reveal>What We Believe</p>
          <AnimatedWords as="h2" text="Four things we'll never compromise." className="about__valuesTitle" />
          <div className="about__valuesGrid">
            {VALUES.map((v) => (
              <article className="value-card" key={v.n} data-reveal>
                <span className="value-card__n">{v.n}</span>
                <h3>{v.title}</h3>
                <p>{v.text}</p>
              </article>
            ))}
          </div>
        </div>
      </section>

      <section className="about__cta panel--sand" aria-label="Taste the story">
        <div className="container about__ctaInner">
          <AnimatedWords as="h2" text="Taste the decade yourself." className="about__ctaTitle" />
          <div className="about__ctaRow" data-reveal>
            <Button to="/menu" variant="solid" arrow="right">Explore the Menu</Button>
            <Link to="/contact" className="lnk">
              Find the atelier
              <span className="lnk__arrow" aria-hidden="true"><ArrowRight size={14} /></span>
            </Link>
          </div>
        </div>
      </section>
    </div>
  );
}
