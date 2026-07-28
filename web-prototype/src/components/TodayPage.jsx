import CycleRing from "./CycleRing";
import {
  BluetoothIcon,
  HeartIcon,
  MoonIcon,
  GlowIcon,
  CloudIcon,
  RainIcon,
  SunIcon,
  MoodFaceIcon,
} from "./icons";
import { CYCLE_DAY, CYCLE_LENGTH } from "../cycleData";

const WEEK_LABELS = ["M", "T", "W", "T", "F", "S", "S"];
const WEEK_WEATHER = [CloudIcon, CloudIcon, RainIcon, SunIcon, SunIcon, RainIcon, RainIcon];

const ENCOURAGEMENT_BY_PHASE = [
  { maxDay: 5, text: "Rest is productive too — let yourself slow down." },
  { maxDay: 13, text: "Your energy is rising — reach for the light." },
  { maxDay: 16, text: "You're glowing today — let it show." },
  { maxDay: 28, text: "Be gentle with yourself as things wind down." },
];

const MOOD_OPTIONS = [
  { id: "down", variant: "down" },
  { id: "low", variant: "low" },
  { id: "neutral", variant: "neutral" },
  { id: "happy", variant: "happy" },
];

function getEncouragement(cycleDay) {
  const phase = ENCOURAGEMENT_BY_PHASE.find((p) => cycleDay <= p.maxDay);
  return phase ? phase.text : ENCOURAGEMENT_BY_PHASE[0].text;
}

const today = new Date();
const todayIndex = (today.getDay() + 6) % 7; // Monday = 0 ... Sunday = 6
const dateLabel = today.toLocaleDateString("en-US", {
  weekday: "long",
  month: "long",
  day: "numeric",
});

export default function TodayPage({
  dayCount,
  mood,
  onSelectMood,
  journal,
  onJournalChange,
}) {
  return (
    <div className="today-page">
      <header className="today-header">
        <div className="today-header__top">
          <div className="day-badge">
            <span className="day-badge__bt">
              <BluetoothIcon size={15} color="var(--color-primary)" />
            </span>
            <span className="day-badge__count">
              {String(dayCount).padStart(3, "0")}
            </span>
          </div>
          <div className="week-strip">
            <div className="week-strip__labels">
              {WEEK_LABELS.map((label, i) => (
                <span
                  key={i}
                  className={`week-strip__label${i === todayIndex ? " week-strip__label--active" : ""}`}
                >
                  {label}
                </span>
              ))}
            </div>
            <div className="week-strip__weather">
              {WEEK_WEATHER.map((Icon, i) => (
                <Icon key={i} size={13} color="var(--color-icon-neutral)" />
              ))}
            </div>
          </div>
        </div>
        <div className="today-header__date">{dateLabel}</div>
      </header>

      <div className="ring-section">
        <CycleRing cycleDay={CYCLE_DAY} cycleLength={CYCLE_LENGTH}>
          <div className="flower-placeholder">flower placeholder</div>
        </CycleRing>
      </div>

      <h1 className="flower-name">Viola Lumina</h1>
      <p className="encouragement">{getEncouragement(CYCLE_DAY)}</p>

      <div className="stats-pill">
        <span className="stats-pill__item">
          <HeartIcon size={13} color="var(--color-primary)" />
          68 bpm
        </span>
        <span className="stats-pill__divider" />
        <span className="stats-pill__item">
          <MoonIcon size={13} color="var(--color-primary)" />
          7h 32m
        </span>
        <span className="stats-pill__divider" />
        <span className="stats-pill__item">
          <GlowIcon size={13} color="var(--color-primary)" />
          72% glow
        </span>
      </div>

      <section className="section">
        <h2 className="section__title">Logs today</h2>
        <textarea
          className="journal-box"
          placeholder="Write anything about your day..."
          value={journal}
          onChange={(e) => onJournalChange(e.target.value)}
        />
      </section>

      <section className="section">
        <h2 className="section__title">Mood today</h2>
        <div className="mood-row">
          {MOOD_OPTIONS.map((option) => {
            const isActive = mood === option.id;
            return (
              <button
                key={option.id}
                type="button"
                className={`mood-btn${isActive ? " mood-btn--active" : ""}`}
                onClick={() => onSelectMood(option.id)}
                aria-label={option.id}
              >
                <MoodFaceIcon
                  size={26}
                  variant={option.variant}
                  color={isActive ? "var(--color-primary)" : "var(--color-text)"}
                />
              </button>
            );
          })}
        </div>
      </section>
    </div>
  );
}
