import { CalendarIcon } from "./icons";

export default function CalendarPage() {
  return (
    <div className="stub-page">
      <div className="stub-page__icon">
        <CalendarIcon size={28} color="var(--color-primary)" />
      </div>
      <h2>日历</h2>
      <p>你的花园历史会在这里出现，敬请期待。</p>
    </div>
  );
}
