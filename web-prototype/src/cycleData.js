export const CYCLE_DAY = 8;
export const CYCLE_LENGTH = 28;

// Colors matched to the actual flower_cycle.html art per stage (not the
// original red/purple/yellow/pink spec) — that sketch renders ovulatory as
// pink/salmon and luteal as yellow/gold, the opposite of the early guess.
export const PHASES = [
  {
    id: "menstrual",
    name: "Menstrual",
    flowerName: "Rosalie Ember",
    color: "#D6566B",
    maxDay: 5,
    description:
      "Estrogen and progesterone are at their lowest as the uterine lining sheds. Energy often dips — rest is expected, not a setback.",
  },
  {
    id: "follicular",
    name: "Follicular",
    flowerName: "Viola Lumina",
    color: "#7958C8",
    maxDay: 13,
    description:
      "Estrogen starts rising as follicles develop in the ovaries, often bringing gains in energy, mood, and skin clarity.",
  },
  {
    id: "ovulatory",
    name: "Ovulatory",
    flowerName: "Aurora Blush",
    color: "#D98CB3",
    maxDay: 16,
    description:
      "A surge in luteinizing hormone triggers the release of an egg. Estrogen peaks, often bringing the most energy of the cycle.",
  },
  {
    id: "luteal",
    name: "Luteal",
    flowerName: "Aurelia Gold",
    color: "#E3B23C",
    maxDay: 28,
    description:
      "Progesterone rises to prepare the uterine lining, then falls if there's no pregnancy — a shift that can bring fatigue or PMS symptoms.",
  },
];

export function getPhaseForCycleDay(cycleDay) {
  const normalized = ((cycleDay - 1) % CYCLE_LENGTH) + 1;
  return PHASES.find((phase) => normalized <= phase.maxDay) ?? PHASES[PHASES.length - 1];
}

const MS_PER_DAY = 86400000;

function startOfDay(date) {
  const d = new Date(date);
  d.setHours(0, 0, 0, 0);
  return d;
}

export const TODAY = startOfDay(new Date());

export const CYCLE_START_DATE = (() => {
  const d = new Date(TODAY);
  d.setDate(d.getDate() - (CYCLE_DAY - 1));
  return d;
})();

export function getCycleDayForDate(date) {
  const day = startOfDay(date);
  const diff = Math.round((day - CYCLE_START_DATE) / MS_PER_DAY);
  const normalized = ((diff % CYCLE_LENGTH) + CYCLE_LENGTH) % CYCLE_LENGTH;
  return normalized + 1;
}

export function isFutureDate(date) {
  return startOfDay(date).getTime() > TODAY.getTime();
}

export function isSameDay(a, b) {
  return startOfDay(a).getTime() === startOfDay(b).getTime();
}
