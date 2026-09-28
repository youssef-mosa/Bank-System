import { useContext, useState } from 'react';
import { BootContext, useOrder } from '../App.jsx';
import { gsap, useGsap, RM, splitWords, initReveals } from '../animations/gsap.js';
import { usePageMeta } from '../utils/seo.js';
import Button from '../components/Button.jsx';
import { ArrowUpRight } from '../components/icons.jsx';
import '../styles/contact.css';

export default function Contact() {
  usePageMeta(
    'Contact & Location',
    'Find IBRIK at 12 Bahgat Ali Street, Zamalek, Cairo. Hours, phone, WhatsApp and wholesale enquiries.'
  );
  const booted = useContext(BootContext);
  const openOrder = useOrder();
  const [form, setForm] = useState({ name: '', email: '', message: '' });

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

  const submit = (e) => {
    e.preventDefault();
    const subject = encodeURIComponent(`Note for IBRIK from ${form.name || 'a guest'}`);
    const body = encodeURIComponent(`${form.message}\n\n— ${form.name} (${form.email})`);
    window.location.href = `mailto:hello@ibrik.coffee?subject=${subject}&body=${body}`;
  };

  const field = (key) => ({
    value: form[key],
    onChange: (e) => setForm((f) => ({ ...f, [key]: e.target.value })),
  });

  return (
    <div ref={scope} className="contact">
      <header className="page-head">
        <div className="container">
          <p className="eyebrow page-head__eyebrow">Contact &amp; Location</p>
          <h1 className="page-head__title">Come sit with us.</h1>
          <p className="page-head__lede">
            Twelve seats in Zamalek, a kettle that's never off, and a standing
            invitation. Walk in, or let the bar know you're coming.
          </p>
        </div>
      </header>

      <div className="container contact__grid">
        <div className="contact__info">
          <section className="contact__block" data-reveal aria-label="Address">
            <h2 className="contact__blockTitle">Visit</h2>
            <p className="contact__big">12 Bahgat Ali Street</p>
            <p>Zamalek, Cairo, Egypt</p>
            <p className="contact__hint">Two minutes from Bahgat Ali square — look for the copper door.</p>
          </section>

          <section className="contact__block" data-reveal aria-label="Opening hours">
            <h2 className="contact__blockTitle">Hours</h2>
            <dl className="contact__hours">
              <div><dt>Sunday – Thursday</dt><dd>7:00 – 23:00</dd></div>
              <div><dt>Friday – Saturday</dt><dd>8:00 – 00:00</dd></div>
            </dl>
            <p className="contact__hint">First ibrik on the flame at 6:45. Last roast logged by 21:00.</p>
          </section>

          <section className="contact__block" data-reveal aria-label="Contact details">
            <h2 className="contact__blockTitle">Reach the bar</h2>
            <ul className="contact__links">
              <li>
                <a href="mailto:hello@ibrik.coffee" className="lnk">
                  hello@ibrik.coffee
                  <span className="lnk__arrow" aria-hidden="true"><ArrowUpRight size={14} /></span>
                </a>
              </li>
              <li>
                <a href="tel:+201002345678" className="lnk">
                  +20 100 234 5678
                  <span className="lnk__arrow" aria-hidden="true"><ArrowUpRight size={14} /></span>
                </a>
              </li>
              <li>
                <a
                  href="https://wa.me/201002345678?text=Hi%20IBRIK%20—%20I%27d%20like%20to%20place%20an%20order."
                  target="_blank"
                  rel="noopener noreferrer"
                  className="lnk"
                >
                  WhatsApp the bar
                  <span className="lnk__arrow" aria-hidden="true"><ArrowUpRight size={14} /></span>
                </a>
              </li>
            </ul>
            <p className="contact__hint">Wholesale &amp; events — write to hello@ibrik.coffee with “wholesale” in the subject.</p>
          </section>

          <div className="contact__cta" data-reveal>
            <Button variant="solid" arrow="right" onClick={() => openOrder()}>Order for pickup</Button>
          </div>
        </div>

        <form className="contact__form" onSubmit={submit} data-reveal aria-label="Send a note">
          <h2 className="contact__formTitle">Leave a note</h2>
          <p className="contact__formLede">
            Events, wholesale, or just to tell us how the Spanish latte was —
            the nib of every message gets read by a human with a cup in hand.
          </p>
          <label className="field">
            <span className="field__label">Your name</span>
            <input type="text" name="name" autoComplete="name" required {...field('name')} />
          </label>
          <label className="field">
            <span className="field__label">Email</span>
            <input type="email" name="email" autoComplete="email" required {...field('email')} />
          </label>
          <label className="field">
            <span className="field__label">Message</span>
            <textarea name="message" rows="5" required {...field('message')} />
          </label>
          <Button type="submit" variant="solid" arrow="right">Send the note</Button>
          <p className="contact__formHint">Opens your mail app — no accounts, no forms-in-the-cloud.</p>
        </form>
      </div>
    </div>
  );
}
