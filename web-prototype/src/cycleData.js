export const CYCLE_DAY = 8;
export const CYCLE_LENGTH = 28;

export const PHASES = [
  { id: "menstrual", name: "Menstrual", color: "#D6566B", maxDay: 5 },
  { id: "follicular", name: "Follicular", color: "#7958C8", maxDay: 13 },
  { id: "ovulatory", name: "Ovulatory", color: "#E3B23C", maxDay: 16 },
  { id: "luteal", name: "Luteal", color: "#D98CB3", maxDay: 28 },
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
