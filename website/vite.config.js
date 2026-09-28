import { defineConfig } from 'vite';
import react from '@vitejs/plugin-react';

export default defineConfig({
  plugins: [react()],
  server: {
    host: '0.0.0.0',
    port: 5173,
    allowedHosts: true,
  },
  preview: {
    host: '0.0.0.0',
    port: 4173,
    allowedHosts: true,
  },
  build: {
    target: 'es2019',
    cssMinify: true,
    rollupOptions: {
      output: {
        // Only chunk for client builds — SSR marks these external.
        manualChunks: process.argv.includes('--ssr')
          ? undefined
          : {
              vendor: ['react', 'react-dom', 'react-router-dom'],
              motion: ['gsap'],
            },
      },
    },
  },
});
