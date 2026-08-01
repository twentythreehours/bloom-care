import { useState } from "react";
import {
  ChevronLeftIcon,
  ChevronRightIcon,
  FlowerIcon,
  SproutIcon,
  HeartIcon,
  MoonIcon,
  GlowIcon,
} from "./icons";
import DayDetailModal from "./DayDetailModal";
import {
  CYCLE_DAY,
  TODAY,
  getCycleDayForDate,
  getPhaseForCycleDay,
  isFutureDate,
  isSameDay,
} from "../cycleData";

const WEEKDAY_LABELS = ["S", "M", "T", "W", "T", "F", "S"];

function buildMonthGrid(viewDate) {
  const year = viewDate.getFullYear();
  const month = viewDate.getMonth();
  const daysInMonth = new Date(year, month + 1, 0).getDate();
  const startWeekday = new Date(year, month, 1).getDay();

  const cells = Array(startWeekday).fill(null);
  for (let day = 1; day <= daysInMonth; day += 1) {
    cells.push(new Date(year, month, day));
  }
  return cells;
}

const todayPhase = getPhaseForCycleDay(CYCLE_DAY);

export default function CalendarPage() {
  const [viewDate, setViewDate] = useState(
    new Date(TODAY.getFullYear(), TODAY.getMonth(), 1),
  );
  const [selectedDate, setSelectedDate] = useState(null);

  const cells = buildMonthGrid(viewDate);
  const monthLabel = viewDate.toLocaleDateString("en-US", {
    month: "long",
    year: "numeric",
  });

  return (
    <div className="calendar-page">
      <header className="calendar-header">
        <button
          type="button"
          className="calendar-nav-btn"
          aria-label="Previous month"
          onClick={() =>
            setViewDate((d) => new Date(d.getFullYear(), d.getMonth() - 1, 1))
          }
        >
          <ChevronLeftIcon size={16} color="var(--color-primary)" />
        </button>
        <div className="calendar-header__title">
          <h1>{monthLabel}</h1>
          <p>
            {todayPhase.name} Phase · Cycle Day {CYCLE_DAY}
          </p>
        </div>
        <button
          type="button"
          className="calendar-nav-btn"
          aria-label="Next month"
          onClick={() =>
            setViewDate((d) => new Date(d.getFullYear(), d.getMonth() + 1, 1))
          }
        >
          <ChevronRightIcon size={16} color="var(--color-primary)" />
        </button>
      </header>

      <div className="calendar-weekdays">
        {WEEKDAY_LABELS.map((label, i) => (
          <span key={i}>{label}</span>
        ))}
      </div>

      <div className="calendar-grid">
        {cells.map((date, i) => {
          if (!date) {
            return <div key={i} className="calendar-cell calendar-cell--empty" />;
          }
          const future = isFutureDate(date);
          const phase = getPhaseForCycleDay(getCycleDayForDate(date));
          const isToday = isSameDay(date, TODAY);
          const className = `calendar-cell${isToday ? " calendar-cell--today" : ""}${future ? "" : " calendar-cell--interactive"}`;

          if (future) {
            return (
              <div key={i} className={className}>
                <SproutIcon size={20} />
                <span className="calendar-cell__day">{date.getDate()}</span>
              </div>
            );
          }

          return (
            <button
              key={i}
              type="button"
              className={className}
              onClick={() => setSelectedDate(date)}
              aria-label={date.toDateString()}
            >
              <FlowerIcon size={30} color={phase.color} />
              <span className="calendar-cell__day">{date.getDate()}</span>
            </button>
          );
        })}
      </div>

      <button
        type="button"
        className="calendar-summary"
        onClick={() => setSelectedDate(TODAY)}
      >
        <div className="calendar-summary__text">
          <span className="calendar-summary__phase">
            {todayPhase.name.toUpperCase()} PHASE
          </span>
          <span className="calendar-summary__date">
            {TODAY.toLocaleDateString("en-US", { month: "long", day: "numeric" })} · Today
          </span>
          <div className="calendar-summary__stats">
            <span>
              <HeartIcon size={12} color="var(--color-primary)" />
              68 bpm
            </span>
            <span>
              <MoonIcon size={12} color="var(--color-primary)" />
              7h 32m
            </span>
            <span>
              <GlowIcon size={12} color="var(--color-primary)" />
              72% O2
            </span>
          </div>
        </div>
        <FlowerIcon size={48} color={todayPhase.color} />
      </button>

      {selectedDate && (
        <DayDetailModal date={selectedDate} onClose={() => setSelectedDate(null)} />
      )}
    </div>
  );
}
