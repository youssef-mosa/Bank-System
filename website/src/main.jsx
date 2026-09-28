import { createRoot } from 'react-dom/client';
import { BrowserRouter } from 'react-router-dom';
import App from './App.jsx';

// Self-hosted variable fonts (no external font requests).
import '@fontsource-variable/fraunces/standard.css';
import '@fontsource-variable/fraunces/standard-italic.css';
import '@fontsource-variable/manrope';

import './styles/global.css';

/**
 * Note: React.StrictMode is intentionally omitted — GSAP timelines are
 * driven from layout effects and the double effect invocation in dev
 * StrictMode makes entrance choreography flicker. Animations are scoped
 * with gsap.context and fully reverted on unmount instead.
 */
createRoot(document.getElementById('root')).render(
  <BrowserRouter>
    <App />
  </BrowserRouter>
);
