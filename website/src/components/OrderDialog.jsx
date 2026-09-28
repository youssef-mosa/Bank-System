import { useEffect, useRef } from 'react';
import { gsap, RM } from '../animations/gsap.js';
import { Close, ArrowUpRight } from './icons.jsx';

const WHATSAPP = '201002345678';
const PHONE = '+201002345678';

/**
 * Order dialog — currently routes to external channels (WhatsApp / phone),
 * structured so a real ordering platform can replace the links later.
 */
export default function OrderDialog({ product, onClose }) {
  const ref = useRef(null);

  useEffect(() => {
    const dialog = ref.current;
    if (!dialog) return;
    if (product && !dialog.open) {
      dialog.showModal();
      document.body.classList.add('dialog-open');
      if (!RM) {
        gsap.fromTo(
          dialog.querySelector('.order-dialog__panel'),
          { y: 36, autoAlpha: 0, scale: 0.97 },
          { y: 0, autoAlpha: 1, scale: 1, duration: 0.55, ease: 'power3.out' }
        );
        gsap.fromTo(
          dialog.querySelectorAll('.order-dialog__row'),
          { y: 18, autoAlpha: 0 },
          { y: 0, autoAlpha: 1, duration: 0.5, stagger: 0.08, delay: 0.15, ease: 'power3.out' }
        );
      }
    }
    if (!product && dialog.open) dialog.close();
  }, [product]);

  const productName = product?.name;
  const waText = encodeURIComponent(
    productName ? `Hi IBRIK — I'd like to order the ${productName}.` : "Hi IBRIK — I'd like to place an order."
  );

  return (
    <dialog
      ref={ref}
      className="order-dialog"
      aria-labelledby="order-dialog-title"
      onClose={() => {
        document.body.classList.remove('dialog-open');
        onClose();
      }}
      onClick={(e) => {
        if (e.target === ref.current) ref.current.close();
      }}
    >
      <div className="order-dialog__panel">
        <button type="button" className="order-dialog__close" aria-label="Close" onClick={() => ref.current.close()}>
          <Close size={16} />
        </button>

        <p className="eyebrow eyebrow--copper">Order Ahead</p>
        <h2 id="order-dialog-title" className="order-dialog__title">
          {productName ? `Order the ${productName}` : 'Order from IBRIK'}
        </h2>
        <p className="order-dialog__note">
          Ping the bar before you leave — your cup will be waiting at the counter.
          12 Bahgat Ali Street, Zamalek.
        </p>

        <div className="order-dialog__rows">
          <a
            className="order-dialog__row"
            href={`https://wa.me/${WHATSAPP}?text=${waText}`}
            target="_blank"
            rel="noopener noreferrer"
          >
            <span>
              <strong>WhatsApp the bar</strong>
              <em>Fastest — usually answered within a minute</em>
            </span>
            <span className="lnk__arrow" aria-hidden="true"><ArrowUpRight size={16} /></span>
          </a>
          <a className="order-dialog__row" href={`tel:${PHONE}`}>
            <span>
              <strong>Call for pickup</strong>
              <em>+20 100 234 5678 · 7:00–23:00</em>
            </span>
            <span className="lnk__arrow" aria-hidden="true"><ArrowUpRight size={16} /></span>
          </a>
          <div className="order-dialog__row order-dialog__row--soon" aria-live="polite">
            <span>
              <strong>Delivery platforms</strong>
              <em>Coming soon — the integration point lives here</em>
            </span>
            <span className="order-dialog__badge">Soon</span>
          </div>
        </div>
      </div>
    </dialog>
  );
}
