/**
 * Converts master images in assets-src/ into responsive WebP variants
 * inside public/images/. Run with: npm run images
 */
import sharp from 'sharp';
import { readdir, mkdir } from 'node:fs/promises';
import path from 'node:path';
import { fileURLToPath } from 'node:url';

const root = path.dirname(fileURLToPath(import.meta.url));
const SRC = path.join(root, '..', 'assets-src');
const OUT = path.join(root, '..', 'public', 'images');

// Product photos are cropped to a consistent 4:5 editorial crop.
const PRODUCT_IDS = [
  'espresso', 'ibrik', 'cortado', 'caramel-latte', 'cold-brew', 'mocha',
  'spanish-latte', 'pistachio-latte', 'flat-white', 'matcha',
];

const jobs = PRODUCT_IDS.map((name) => ({ name, widths: [480, 800, 1100], aspect: 4 / 5 }));

async function run() {
  await mkdir(OUT, { recursive: true });
  const files = await readdir(SRC);

  for (const job of jobs) {
    const entry = files.find((f) => f.startsWith(job.name + '.'));
    if (!entry) {
      console.warn(`  ! missing master for "${job.name}"`);
      continue;
    }
    const input = path.join(SRC, entry);
    const meta = await sharp(input).metadata();
    console.log(`→ ${job.name} (${meta.width}x${meta.height})`);

    for (const w of job.widths) {
      let pipeline = sharp(input);
      if (job.aspect) {
        const h = Math.round(w / job.aspect);
        pipeline = pipeline.resize(w, h, { fit: 'cover', position: 'entropy', withoutEnlargement: false });
      } else {
        pipeline = pipeline.resize(w, null, { withoutEnlargement: true });
      }
      await pipeline.webp({ quality: 80, effort: 4 }).toFile(path.join(OUT, `${job.name}-${w}.webp`));
    }
  }

  // Open Graph image (1200x630) derived from the signature serve.
  const ogSource = files.find((f) => f.startsWith('ibrik.'));
  if (ogSource) {
    await sharp(path.join(SRC, ogSource))
      .resize(1200, 630, { fit: 'cover', position: 'attention' })
      .jpeg({ quality: 84 })
      .toFile(path.join(OUT, '..', 'og-image.jpg'));
    console.log('→ og-image.jpg');
  }
  console.log('Done.');
}

run().catch((err) => {
  console.error(err);
  process.exit(1);
});
