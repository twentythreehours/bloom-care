import { useState } from "react";
import {
  BluetoothIcon,
  BellIcon,
  ClockIcon,
  ShieldIcon,
  GlobeIcon,
  HelpCircleIcon,
  ChevronRightIcon,
  LogOutIcon,
} from "./icons";

const USER = {
  name: "User Name",
  tagline: "Growing Day 001",
  initials: "U",
};

const SETTINGS_LINKS = [
  { id: "privacy", label: "Privacy & Data", Icon: ShieldIcon },
  { id: "language", label: "Language & Units", Icon: GlobeIcon },
  { id: "help", label: "Help & Support", Icon: HelpCircleIcon },
];

function ToggleSwitch({ checked, onChange, label }) {
  return (
    <button
      type="button"
      role="switch"
      aria-checked={checked}
      aria-label={label}
      className={`toggle${checked ? " toggle--on" : ""}`}
      onClick={() => onChange((value) => !value)}
    >
      <span className="toggle__thumb" />
    </button>
  );
}

export default function ProfilePage() {
  const [isPaired, setIsPaired] = useState(true);
  const [notifications, setNotifications] = useState(true);
  const [reminders, setReminders] = useState(false);

  return (
    <div className="profile-page">
      <div className="profile-header">
        <div className="profile-avatar">{USER.initials}</div>
        <div>
          <h1 className="profile-name">{USER.name}</h1>
          <p className="profile-tagline">{USER.tagline}</p>
        </div>
      </div>

      <section className="section">
        <h2 className="section__title">Device</h2>
        <div className="device-card">
          <span className="device-card__icon">
            <BluetoothIcon size={16} color="var(--color-primary)" />
          </span>
          <div className="device-card__info">
            <span className="device-card__name">Bloom Sensor 001</span>
            <span
              className={`device-card__status${isPaired ? " device-card__status--connected" : ""}`}
            >
              {isPaired ? "Connected · 84% battery" : "Not connected"}
            </span>
          </div>
          <button
            type="button"
            className="device-card__action"
            onClick={() => setIsPaired((v) => !v)}
          >
            {isPaired ? "Disconnect" : "Pair"}
          </button>
        </div>
      </section>

      <section className="section">
        <h2 className="section__title">Settings</h2>
        <div className="settings-list">
          <div className="settings-row">
            <span className="settings-row__icon">
              <BellIcon size={17} color="var(--color-primary)" />
            </span>
            <span className="settings-row__label">Notifications</span>
            <ToggleSwitch
              label="Notifications"
              checked={notifications}
              onChange={setNotifications}
            />
          </div>
          <div className="settings-row">
            <span className="settings-row__icon">
              <ClockIcon size={17} color="var(--color-primary)" />
            </span>
            <span className="settings-row__label">Daily Reminders</span>
            <ToggleSwitch
              label="Daily Reminders"
              checked={reminders}
              onChange={setReminders}
            />
          </div>
          {SETTINGS_LINKS.map(({ id, label, Icon }) => (
            <button key={id} type="button" className="settings-row settings-row--link">
              <span className="settings-row__icon">
                <Icon size={17} color="var(--color-primary)" />
              </span>
              <span className="settings-row__label">{label}</span>
              <ChevronRightIcon size={15} color="var(--color-text-muted)" />
            </button>
          ))}
        </div>
      </section>

      <button type="button" className="logout-btn">
        <LogOutIcon size={16} color="#b4485c" />
        Log out
      </button>

      <p className="profile-footer">Bloom · prototype v0.1</p>
    </div>
  );
}
