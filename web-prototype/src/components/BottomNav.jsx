import { HomeIcon, CalendarIcon, ProfileIcon } from "./icons";

const TABS = [
  { id: "today", label: "Today", Icon: HomeIcon },
  { id: "calendar", label: "Calendar", Icon: CalendarIcon },
  { id: "profile", label: "Profile", Icon: ProfileIcon },
];

export default function BottomNav({ active, onChange }) {
  return (
    <nav className="bottom-nav">
      {TABS.map(({ id, label, Icon }) => {
        const isActive = active === id;
        return (
          <button
            key={id}
            type="button"
            className={`bottom-nav__item${isActive ? " bottom-nav__item--active" : ""}`}
            onClick={() => onChange(id)}
          >
            <Icon
              size={20}
              color={isActive ? "var(--color-primary)" : "var(--color-text-muted)"}
            />
            <span>{label}</span>
          </button>
        );
      })}
    </nav>
  );
}
