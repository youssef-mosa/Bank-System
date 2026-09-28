import { Link } from 'react-router-dom';
import SmartImage from './SmartImage.jsx';
import { ArrowRight } from './icons.jsx';
import { CATEGORY_LABELS, formatPrice } from '../data/products.js';

/**
 * Editorial product card used across featured sections and the menu grid.
 */
export default function ProductCard({ product, eager = false, className = '' }) {
  return (
    <Link
      to={`/products/${product.slug}`}
      className={`product-card ${className}`}
      data-flip-id={product.slug}
      aria-label={`${product.name} — ${formatPrice(product.price)}`}
    >
      <figure className="product-card__media">
        <SmartImage
          name={product.image}
          alt={product.alt}
          sizes="(max-width: 760px) 94vw, (max-width: 1100px) 46vw, 30vw"
          eager={eager}
        />
      </figure>
      <div className="product-card__body">
        <div className="product-card__info">
          <span className="product-card__cat">{CATEGORY_LABELS[product.category]}</span>
          <h3 className="product-card__name">{product.name}</h3>
          <p className="product-card__tag">{product.tagline}</p>
        </div>
        <span className="product-card__price">{formatPrice(product.price)}</span>
      </div>
      <span className="product-card__view">
        View Product
        <span className="product-card__viewArrow" aria-hidden="true">
          <ArrowRight size={14} />
        </span>
      </span>
    </Link>
  );
}
