import { createContext, useCallback, useContext, useEffect, useState, lazy, Suspense } from 'react';
import { Routes, Route, useLocation } from 'react-router-dom';
import Navbar from './components/Navbar.jsx';
import Footer from './components/Footer.jsx';
import Boot from './components/Boot.jsx';
import OrderDialog from './components/OrderDialog.jsx';
import Home from './pages/Home.jsx';
import { ScrollTrigger } from './animations/gsap.js';

const Menu = lazy(() => import('./pages/Menu.jsx'));
const ProductDetails = lazy(() => import('./pages/ProductDetails.jsx'));
const About = lazy(() => import('./pages/About.jsx'));
const Contact = lazy(() => import('./pages/Contact.jsx'));
const NotFound = lazy(() => import('./pages/NotFound.jsx'));

/** True once the one-time boot sequence has completed. */
export const BootContext = createContext(true);

/** Opens the global order dialog, optionally for a specific product. */
const OrderContext = createContext(() => {});
export const useOrder = () => useContext(OrderContext);

function ScrollManager() {
  const { pathname } = useLocation();
  useEffect(() => {
    window.scrollTo({ top: 0, left: 0, behavior: 'instant' });
    // Layout changed — let ScrollTrigger recompute after paint.
    const t = requestAnimationFrame(() => ScrollTrigger.refresh());
    return () => cancelAnimationFrame(t);
  }, [pathname]);
  return null;
}

function PageFallback() {
  return (
    <div className="page-fallback" role="status" aria-label="Loading page">
      <span className="page-fallback__line" />
    </div>
  );
}

export default function App() {
  const [booted, setBooted] = useState(false);
  const [orderProduct, setOrderProduct] = useState(null); // null = closed, {} = generic
  const openOrder = useCallback((product = null) => setOrderProduct(product ?? {}), []);
  const closeOrder = useCallback(() => setOrderProduct(null), []);

  return (
    <BootContext.Provider value={booted}>
      <OrderContext.Provider value={openOrder}>
        <Boot onDone={() => setBooted(true)} />
        <a className="skip-link" href="#main">Skip to content</a>
        <Navbar />
        <ScrollManager />
        <main id="main">
          <Suspense fallback={<PageFallback />}>
            <Routes>
              <Route path="/" element={<Home />} />
              <Route path="/menu" element={<Menu />} />
              <Route path="/products/:slug" element={<ProductDetails />} />
              <Route path="/about" element={<About />} />
              <Route path="/contact" element={<Contact />} />
              <Route path="*" element={<NotFound />} />
            </Routes>
          </Suspense>
        </main>
        <Footer />
        <OrderDialog product={orderProduct} onClose={closeOrder} />
      </OrderContext.Provider>
    </BootContext.Provider>
  );
}
