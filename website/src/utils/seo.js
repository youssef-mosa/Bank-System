import { useEffect } from 'react';

const SITE = 'IBRIK — Cairo Coffee Atelier';

/**
 * Per-route document title + meta description management for the SPA.
 */
export function usePageMeta(title, description) {
  useEffect(() => {
    document.title = title ? `${title} — IBRIK Coffee` : SITE;
    if (description) {
      let meta = document.querySelector('meta[name="description"]');
      if (!meta) {
        meta = document.createElement('meta');
        meta.setAttribute('name', 'description');
        document.head.appendChild(meta);
      }
      meta.setAttribute('content', description);
    }
  }, [title, description]);
}

/**
 * Injects a JSON-LD structured-data script while the component is mounted.
 */
export function useJsonLd(id, data) {
  useEffect(() => {
    if (!data) return undefined;
    const script = document.createElement('script');
    script.type = 'application/ld+json';
    script.id = `ld-${id}`;
    script.textContent = JSON.stringify(data);
    document.head.appendChild(script);
    return () => script.remove();
  }, [id, data]);
}

export const ORG_JSONLD = {
  '@context': 'https://schema.org',
  '@type': 'CafeOrCoffeeShop',
  name: 'IBRIK — Cairo Coffee Atelier',
  slogan: 'The quiet art of qahwa.',
  servesCuisine: 'Specialty Coffee',
  priceRange: 'EGP 75–150',
  address: {
    '@type': 'PostalAddress',
    streetAddress: '12 Bahgat Ali Street, Zamalek',
    addressLocality: 'Cairo',
    addressCountry: 'EG',
  },
  telephone: '+20-100-234-5678',
  email: 'hello@ibrik.coffee',
  openingHours: ['Su-Th 07:00-23:00', 'Fr-Sa 08:00-24:00'],
};
