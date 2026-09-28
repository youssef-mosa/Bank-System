import { Link } from 'react-router-dom';
import { usePageMeta } from '../utils/seo.js';
import Button from '../components/Button.jsx';

export default function NotFound() {
  usePageMeta('Page not found', 'This pour is not on the list.');
  return (
    <section className="notfound panel--dark">
      <div className="container notfound__inner">
        <p className="eyebrow eyebrow--copper">404</p>
        <h1 className="notfound__title">This pour isn't on the list.</h1>
        <p className="notfound__lede">
          The page you're looking for has been drunk, archived, or never existed.
          The menu, however, is very real.
        </p>
        <div className="notfound__ctas">
          <Button to="/menu" variant="cream" arrow="right">Explore the Menu</Button>
          <Link to="/" className="lnk lnk--onDark">Back home</Link>
        </div>
      </div>
    </section>
  );
}
