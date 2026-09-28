/**
 * Single source of truth for the IBRIK catalog.
 * To add a product: drop a 4:5 master into assets-src/, run `npm run images`,
 * then add an entry here. Everything else (menu, filters, product page,
 * structured data) picks it up automatically.
 */

export const CATEGORIES = [
  { id: 'all', label: 'All' },
  { id: 'hot', label: 'Espresso & Hot' },
  { id: 'iced', label: 'Iced Pours' },
  { id: 'specialty', label: 'Specialty' },
];

export const CATEGORY_LABELS = Object.fromEntries(
  CATEGORIES.filter((c) => c.id !== 'all').map((c) => [c.id, c.label])
);

const products = [
  {
    id: 1,
    slug: 'signature-espresso',
    name: 'Signature Espresso',
    category: 'hot',
    price: 75,
    image: 'espresso',
    alt: 'Double espresso with rich golden crema in a matte dark ceramic demitasse',
    tagline: 'Our house trio, pulled ristretto.',
    description:
      'Haraz, Guji and Huila lots blended for Cairo mornings — pulled short and slow for a syrupy, caramel-dark shot with a crema that holds its shape to the last sip.',
    ingredients: ['Single-origin arabica blend', 'Filtered Nile-softened water'],
    flavor: ['Dark chocolate', 'Molasses', 'Orange peel'],
    serve: { temp: 'Hot, 93°C', volume: '30 ml', milk: 'None', note: 'Ceramic demitasse, warmed' },
    nutrition: { kcal: 9, fat: '0 g', carbs: '1 g', protein: '0 g', caffeine: '120 mg' },
    featured: true,
  },
  {
    id: 2,
    slug: 'turkish-ibrik',
    name: 'Turkish Ibrik',
    category: 'hot',
    price: 85,
    image: 'ibrik',
    alt: 'Hand-hammered copper cezve beside a porcelain finjan of Turkish coffee with cardamom pods',
    tagline: 'Five centuries in a copper pot.',
    description:
      'Finely milled Yemeni beans slow-simmered in a hand-hammered copper ibrik with a whisper of cardamom. Poured unfiltered, rested one minute, served the way it has been for five centuries.',
    ingredients: ['Yemeni Haraz beans, finely milled', 'Green cardamom', 'Cane sugar (optional)'],
    flavor: ['Spiced', 'Dense', 'Honeyed'],
    serve: { temp: 'Hot', volume: '70 ml', milk: 'None', note: 'Copper ibrik, porcelain finjan' },
    nutrition: { kcal: 14, fat: '0 g', carbs: '2 g', protein: '0 g', caffeine: '95 mg' },
    featured: true,
  },
  {
    id: 3,
    slug: 'cortado',
    name: 'Cortado',
    category: 'hot',
    price: 80,
    image: 'cortado',
    alt: 'Cortado in a small clear glass with distinct layers of espresso and steamed milk',
    tagline: "The quiet professional's order.",
    description:
      'Equal parts double espresso and silk-steamed milk, served in a small glass. No foam theatre, no syrup — just balance you can hold in two fingers.',
    ingredients: ['Double espresso', 'Steamed Egyptian buffalo milk'],
    flavor: ['Balanced', 'Nutty', 'Velvet'],
    serve: { temp: 'Hot', volume: '120 ml', milk: 'Buffalo milk', note: 'Clear Gibraltar glass' },
    nutrition: { kcal: 62, fat: '3.1 g', carbs: '5 g', protein: '3.2 g', caffeine: '120 mg' },
    featured: false,
  },
  {
    id: 4,
    slug: 'caramel-latte',
    name: 'Caramel Latte',
    category: 'hot',
    price: 90,
    image: 'caramel-latte',
    alt: 'Caramel latte in a beige ceramic cup with rosetta latte art and caramel drizzle',
    tagline: 'Burnt sugar, winter evenings.',
    description:
      'Cane sugar caramelized in-house until it smells like a December evening in Garden City, folded into textured milk and a double shot, finished with a fine caramel thread.',
    ingredients: ['Double espresso', 'Steamed buffalo milk', 'House caramel'],
    flavor: ['Caramel', 'Toffee', 'Round'],
    serve: { temp: 'Hot', volume: '240 ml', milk: 'Buffalo milk', note: 'Glazed ceramic cup' },
    nutrition: { kcal: 184, fat: '6.8 g', carbs: '24 g', protein: '7.1 g', caffeine: '120 mg' },
    featured: true,
  },
  {
    id: 5,
    slug: 'vanilla-cold-brew',
    name: 'Vanilla Cold Brew',
    category: 'iced',
    price: 100,
    image: 'cold-brew',
    alt: 'Tall glass of cold brew coffee over one large clear ice cube with a vanilla pod beside it',
    tagline: 'Eighteen hours, no shortcuts.',
    description:
      'Coarse-ground Guji steeped cold for eighteen hours, cut with Madagascar vanilla and poured over a single hand-carved clear cube. Sweet without sugar, heavy only in patience.',
    ingredients: ['18-hour cold-steeped Guji', 'Madagascar vanilla', 'Clear ice'],
    flavor: ['Cacao nib', 'Vanilla', 'Silky'],
    serve: { temp: 'Iced', volume: '280 ml', milk: 'None', note: 'Tall glass, one clear cube' },
    nutrition: { kcal: 18, fat: '0 g', carbs: '3 g', protein: '0 g', caffeine: '185 mg' },
    featured: true,
  },
  {
    id: 6,
    slug: 'iced-mocha',
    name: 'Iced Mocha',
    category: 'iced',
    price: 95,
    image: 'mocha',
    alt: 'Iced mocha in a tall glass with swirls of chocolate and milk through espresso over ice',
    tagline: 'Dessert that still counts as coffee.',
    description:
      'Single-origin espresso poured over a cold ganache of 70% dark chocolate and chilled milk. The swirls settle slowly; drink it before they do.',
    ingredients: ['Double espresso', '70% dark chocolate ganache', 'Chilled buffalo milk', 'Clear ice'],
    flavor: ['Cocoa', 'Espresso', 'Cold cream'],
    serve: { temp: 'Iced', volume: '300 ml', milk: 'Buffalo milk', note: 'Tall glass, cocoa dust' },
    nutrition: { kcal: 243, fat: '9.4 g', carbs: '31 g', protein: '8.3 g', caffeine: '130 mg' },
    featured: false,
  },
  {
    id: 7,
    slug: 'spanish-latte',
    name: 'Spanish Latte',
    category: 'iced',
    price: 95,
    image: 'spanish-latte',
    alt: 'Spanish latte in a tall glass with a condensed milk layer beneath golden espresso over ice',
    tagline: 'Our most ordered pour.',
    description:
      'A ribbon of condensed milk, clear ice, and a double shot pulled directly over the top. Sweet, silken and unreasonably smooth — our sweetest sin and our bestseller for a reason.',
    ingredients: ['Double espresso', 'Condensed milk', 'Buffalo milk', 'Clear ice'],
    flavor: ['Condensed sweetness', 'Malt', 'Smooth'],
    serve: { temp: 'Iced', volume: '300 ml', milk: 'Condensed + buffalo milk', note: 'Tall glass, layered' },
    nutrition: { kcal: 212, fat: '7.2 g', carbs: '29 g', protein: '7.8 g', caffeine: '120 mg' },
    featured: false,
  },
  {
    id: 8,
    slug: 'pistachio-latte',
    name: 'Pistachio Latte',
    category: 'specialty',
    price: 120,
    image: 'pistachio-latte',
    alt: 'Pistachio latte in a sand-colored ceramic cup topped with crushed green pistachios',
    tagline: 'A Cairo garden after rain.',
    description:
      'House-made cream of roasted Aleppo pistachios, a double shot and steamed milk, crowned with crushed raw kernels. Green, nutty and quietly extravagant.',
    ingredients: ['Double espresso', 'House pistachio cream', 'Steamed buffalo milk', 'Crushed pistachio'],
    flavor: ['Roasted pistachio', 'Butter', 'Soft earth'],
    serve: { temp: 'Hot or iced', volume: '240 ml', milk: 'Buffalo milk', note: 'Sand-glazed cup' },
    nutrition: { kcal: 226, fat: '12.1 g', carbs: '21 g', protein: '8.9 g', caffeine: '120 mg' },
    featured: true,
  },
  {
    id: 9,
    slug: 'date-flat-white',
    name: 'Date & Honey Flat White',
    category: 'specialty',
    price: 105,
    image: 'flat-white',
    alt: 'Flat white with velvet tulip latte art, two Medjool dates and a jar of honey on the saucer',
    tagline: 'Sweetness with roots.',
    description:
      'Siwa date molasses and Delta honey folded under a double ristretto and velvet-poured milk. An old Egyptian pantry, meeting a very modern cup.',
    ingredients: ['Double ristretto', 'Siwa date molasses', 'Delta honey', 'Steamed buffalo milk'],
    flavor: ['Date', 'Wild honey', 'Molasses'],
    serve: { temp: 'Hot', volume: '180 ml', milk: 'Buffalo milk', note: 'Taupe ceramic cup' },
    nutrition: { kcal: 168, fat: '5.9 g', carbs: '23 g', protein: '6.4 g', caffeine: '110 mg' },
    featured: true,
  },
  {
    id: 10,
    slug: 'rose-matcha',
    name: 'Rose Matcha',
    category: 'specialty',
    price: 110,
    image: 'matcha',
    alt: 'Rose matcha latte in a tall glass layered with rose-infused milk and green matcha over ice',
    tagline: 'Cairo meets Uji.',
    description:
      'Ceremonial-grade matcha whisked to a jade foam and floated over rose-infused milk. Two old tea cultures, one tall glass, no coffee in sight.',
    ingredients: ['Ceremonial matcha', 'Damascene rose water', 'Buffalo milk', 'Clear ice'],
    flavor: ['Grassy', 'Petal', 'Umami'],
    serve: { temp: 'Iced', volume: '300 ml', milk: 'Buffalo milk', note: 'Tall glass, layered' },
    nutrition: { kcal: 142, fat: '5.1 g', carbs: '18 g', protein: '6.1 g', caffeine: '70 mg' },
    featured: false,
  },
];

export default products;
export const featuredProducts = products.filter((p) => p.featured);
export const getProduct = (slug) => products.find((p) => p.slug === slug);
export const formatPrice = (p) => `EGP ${p}`;
