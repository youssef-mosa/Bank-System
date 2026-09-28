/**
 * SSR smoke test — renders every route through React to catch runtime
 * errors that a production build can't surface (no browser needed).
 * Run: npx vite build --ssr scripts/render.mjs --outDir dist-ssr
 *      node scripts/ssr-check.mjs
 */
import { renderToString } from 'react-dom/server';
import { createElement } from 'react';
import { StaticRouter } from 'react-router-dom/server';
import { Routes, Route } from 'react-router-dom';
import App from '../src/App.jsx';
import Menu from '../src/pages/Menu.jsx';
import ProductDetails from '../src/pages/ProductDetails.jsx';
import About from '../src/pages/About.jsx';
import Contact from '../src/pages/Contact.jsx';
import NotFound from '../src/pages/NotFound.jsx';

export function render(url) {
  return renderToString(createElement(StaticRouter, { location: url }, createElement(App)));
}

// Pages are lazy inside App — render them directly too so their code runs.
export function renderPages() {
  const wrap = (el) => renderToString(createElement(StaticRouter, { location: '/x' }, el));
  return {
    Menu: wrap(createElement(Menu)).length,
    About: wrap(createElement(About)).length,
    Contact: wrap(createElement(Contact)).length,
    NotFound: wrap(createElement(NotFound)).length,
  };
}

export function renderProduct(slug) {
  return renderToString(
    createElement(
      StaticRouter,
      { location: `/products/${slug}` },
      createElement(Routes, null, createElement(Route, { path: '/products/:slug', element: createElement(ProductDetails) }))
    )
  ).length;
}
