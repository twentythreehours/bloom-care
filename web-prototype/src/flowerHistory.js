import { getCycleDayForDate, getPhaseForCycleDay } from "./cycleData";
import { summarize } from "./sensor/dailyDataService";
import { mapToFlowerParameters } from "./sensor/flowerMapper";

// There's no real sensor history to replay, so a past day's flower is
// reconstructed deterministically from its date instead — the same day
// always regenerates the same reading rather than re-rolling every visit,
// which is what makes it feel like a stored history rather than noise.
// The reading itself is a genuine average: we simulate a day's worth of
// samples and run them through the same summarize()/flowerMapper pipeline
// the live sensor uses, rather than faking a single "summary" number.

const MOOD_IDS = ["down", "low", "neutral", "happy"];
const JOURNAL_SNIPPETS = [
  "Felt calm and focused most of the day.",
  "A little tired, but pushed through with tea and stretching.",
  "Great energy today — got through my to-do list early.",
  "Slept in and took it slow this morning.",
  "Some cramping in the afternoon, rested more than usual.",
  "Went for a walk and felt recharged.",
  "Busy day at work, but ended it with a good book.",
  "Craving something sweet all day.",
  "Meditated for ten minutes before bed.",
  "A bit emotional today, but felt better after a good cry.",
  "Low motivation this morning, better by evening.",
  "Skin felt great, energy matched it.",
];

const SAMPLES_PER_DAY = 24; // one per hour

function dateKey(date) {
  return date.toISOString().slice(0, 10);
}

function seedFromString(str) {
  let h = 0;
  for (let i = 0; i < str.length; i += 1) {
    h = (h * 31 + str.charCodeAt(i)) | 0;
  }
  return h;
}

// mulberry32 — small, fast, deterministic PRNG from an integer seed.
function mulberry32(seed) {
  let a = seed;
  return function random() {
    a |= 0;
    a = (a + 0x6d2b79f5) | 0;
    let t = Math.imul(a ^ (a >>> 15), 1 | a);
    t = (t + Math.imul(t ^ (t >>> 7), 61 | t)) ^ t;
    return ((t ^ (t >>> 14)) >>> 0) / 4294967296;
  };
}

function clamp(value, min, max) {
  return Math.min(max, Math.max(min, value));
}

function buildDaySamples(random) {
  let heartbeat = 62 + random() * 26;
  let spo2 = 95 + random() * 4;
  let skinTemp = 36.3 + random() * 0.5;
  let activity = 15 + random() * 55;

  const samples = [];
  for (let i = 0; i < SAMPLES_PER_DAY; i += 1) {
    heartbeat = clamp(heartbeat + (random() - 0.5) * 8, 55, 105);
    spo2 = clamp(spo2 + (random() - 0.5) * 2, 93, 100);
    skinTemp = clamp(skinTemp + (random() - 0.5) * 0.2, 36.1, 37.0);
    activity = clamp(activity + (random() - 0.5) * 20, 5, 95);
    samples.push({ heartbeat, spo2, skin_temp: skinTemp, activity });
  }
  return samples;
}

export function getSimulatedDayData(date) {
  const random = mulberry32(seedFromString(dateKey(date)));

  const cycleDay = getCycleDayForDate(date);
  const phase = getPhaseForCycleDay(cycleDay);

  const samples = buildDaySamples(random);
  const summary = summarize(samples);
  const flowerParameters = mapToFlowerParameters(summary);

  const sleepMinutes = Math.round(390 + random() * 150);
  const mood = MOOD_IDS[Math.floor(random() * MOOD_IDS.length)];
  const journal = JOURNAL_SNIPPETS[Math.floor(random() * JOURNAL_SNIPPETS.length)];

  return {
    cycleDay,
    phase,
    flowerName: phase.flowerName,
    sensor: {
      heartbeat: summary.averageHeartbeat,
      spo2: summary.averageSpo2,
      skinTemp: summary.averageSkinTemp,
      activity: summary.averageActivity,
    },
    bpmDisplay: Math.round(summary.averageHeartbeat),
    glow: Math.round(flowerParameters.saturation * 100),
    sleepMinutes,
    mood,
    journal,
  };
}

export function formatSleep(minutes) {
  const h = Math.floor(minutes / 60);
  const m = minutes % 60;
  return `${h}h ${m}m`;
}
