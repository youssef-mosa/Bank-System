# IBRIK — Cairo Coffee Atelier

A premium coffee brand showcase: brand story, animated product catalog,
editorial product pages and an order-ahead interaction. Built as a portfolio/
case-study grade site — luxury, warm, cinematic, and fast.

> Fictional premium Egyptian coffee brand. English-first, structured for a
> future Arabic/RTL locale.

## Stack

- **Vite + React 18** (SPA, code-split routes)
- **GSAP 3** — ScrollTrigger, Flip, timelines (the only animation library)
- Custom design-system CSS (no UI frameworks)
- Self-hosted variable fonts: **Fraunces** (display serif) + **Manrope** (sans)
- Responsive **WebP** images generated from masters via `sharp`

## Commands

```bash
npm install        # install dependencies
npm run dev        # dev server (0.0.0.0:5173)
npm run build      # production build → dist/
npm run preview    # serve the production build
npm run images     # assets-src/*.jpg → public/images/*.webp (responsive)
```

## Architecture

```
src/
├── animations/gsap.js      # gsap setup, useGsap hook, splitWords, reveals,
│                           #   parallax helpers — every animation entry point
├── components/             # Navbar, Footer, Boot (loader), OrderDialog,
│                           #   Button, ProductCard, SmartImage, RevealImg,
│                           #   SectionTitle, AnimatedWords, icons
├── data/products.js        # SINGLE SOURCE OF TRUTH for the catalog
├── pages/                  # Home, Menu, ProductDetails, About, Contact, 404
├── styles/                 # global.css (tokens/reset/shared) + page CSS
└── utils/seo.js            # per-route title/meta + JSON-LD injection
```

### Adding a product

1. Drop a 4:5 master into `assets-src/` (e.g. `saffron-latte.jpg`).
2. Add its id to `PRODUCT_IDS` in `scripts/optimize-images.mjs`, run `npm run images`.
3. Add an entry in `src/data/products.js` (slug, price, ingredients…).
   Menu, filters, product page, related items and JSON-LD all pick it up.

### Order integration

`OrderDialog` currently deep-links to WhatsApp (`wa.me`) and `tel:`. Swap the
`WHATSAPP` / `PHONE` constants in `src/components/OrderDialog.jsx` for a real
ordering endpoint, or replace the rows with your checkout — every “Order Now”
button in the app funnels through `useOrder()` → this one dialog.

## Performance

- Transform/opacity-only motion; `will-change` avoided
- Images: responsive `srcset` WebP (~15–110 KB each), lazy below the fold,
  aspect-ratio reserved (no CLS), hero preloaded
- Route-level code splitting; gsap in its own cached chunk
- Every animation runs in `gsap.context` and reverts on unmount
- `prefers-reduced-motion` fully honored (boot skipped, reveals disabled,
  pinned craft chapter becomes a stacked list)

## Accessibility

Semantic landmarks & headings, keyboard-navigable menu/dialog (`<dialog>`,
ESC, focus return), visible focus rings, alt text everywhere, aria-live
filter counts, split-text kept accessible via `aria-label`.

## RTL readiness

CSS uses logical properties (`inset-inline`, `padding-inline`, …) throughout;
`index.html` carries explicit `lang`/`dir`. Arabic copy flips with `dir="rtl"`.
