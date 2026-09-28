import { render, renderPages, renderProduct } from '../dist-ssr/render.js';

let failed = false;

for (const url of ['/', '/menu', '/products/signature-espresso', '/products/turkish-ibrik', '/about', '/contact', '/nope']) {
  try {
    const html = render(url);
    console.log(`OK   ${url}  (${html.length} chars)`);
  } catch (err) {
    failed = true;
    console.error(`FAIL ${url}: ${err.message}`);
  }
}

try {
  const pages = renderPages();
  for (const [name, len] of Object.entries(pages)) {
    console.log(`OK   <${name}> direct render (${len})`);
  }
  console.log(`OK   <ProductDetails> full route render (${renderProduct('pistachio-latte')})`);
  console.log(`OK   <ProductDetails> unknown slug render (${renderProduct('does-not-exist')})`);
} catch (err) {
  failed = true;
  console.error(`FAIL direct page render: ${err.message}\n${err.stack}`);
}

process.exit(failed ? 1 : 0);
