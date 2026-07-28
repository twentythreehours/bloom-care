export function BluetoothIcon({ size = 15, color = "#7958C8" }) {
  return (
    <svg width={size} height={size} viewBox="0 0 15 15" fill="none">
      <path
        d="M4.375 4.375L10.625 10.625L7.5 13.75V1.25L10.625 4.375L4.375 10.625"
        stroke={color}
        strokeWidth={1.25}
        strokeLinecap="round"
        strokeLinejoin="round"
      />
    </svg>
  );
}

export function HeartIcon({ size = 13, color = "#7958C8" }) {
  return (
    <svg width={size} height={size} viewBox="0 0 13 13" fill="none">
      <path
        d="M10.2917 7.58333C11.0988 6.7925 11.9167 5.84458 11.9167 4.60417C11.9167 3.81404 11.6028 3.05628 11.0441 2.49758C10.4854 1.93888 9.72762 1.625 8.9375 1.625C7.98417 1.625 7.3125 1.89583 6.5 2.70833C5.6875 1.89583 5.01583 1.625 4.0625 1.625C3.27238 1.625 2.51461 1.93888 1.95591 2.49758C1.39721 3.05628 1.08333 3.81404 1.08333 4.60417C1.08333 5.85 1.89583 6.79792 2.70833 7.58333L6.5 11.375L10.2917 7.58333Z"
        stroke={color}
        strokeWidth={1.08333}
        strokeLinecap="round"
        strokeLinejoin="round"
      />
    </svg>
  );
}

export function MoonIcon({ size = 13, color = "#7958C8" }) {
  return (
    <svg width={size} height={size} viewBox="0 0 13 13" fill="none">
      <path
        d="M6.5 1.625C5.85353 2.27146 5.49035 3.14826 5.49035 4.0625C5.49035 4.97674 5.85353 5.85353 6.5 6.5C7.14647 7.14647 8.02326 7.50965 8.9375 7.50965C9.85174 7.50965 10.7285 7.14647 11.375 6.5C11.375 7.46418 11.0891 8.40672 10.5534 9.2084C10.0177 10.0101 9.25637 10.6349 8.36558 11.0039C7.47479 11.3729 6.49459 11.4694 5.54893 11.2813C4.60328 11.0932 3.73464 10.6289 3.05285 9.94715C2.37107 9.26536 1.90677 8.39672 1.71867 7.45107C1.53057 6.50541 1.62711 5.52521 1.99609 4.63442C2.36506 3.74363 2.98991 2.98226 3.7916 2.44659C4.59328 1.91091 5.53582 1.625 6.5 1.625Z"
        stroke={color}
        strokeWidth={1.08333}
        strokeLinecap="round"
        strokeLinejoin="round"
      />
    </svg>
  );
}

export function GlowIcon({ size = 13, color = "#7958C8" }) {
  return (
    <svg width={size} height={size} viewBox="0 0 13 13" fill="none">
      <path
        d="M11.9167 6.5H10.5733C10.3366 6.49949 10.1062 6.57654 9.91744 6.71936C9.72865 6.86217 9.59183 7.0629 9.52792 7.29083L8.255 11.8192C8.2468 11.8473 8.22969 11.872 8.20625 11.8896C8.18281 11.9072 8.1543 11.9167 8.125 11.9167C8.0957 11.9167 8.06719 11.9072 8.04375 11.8896C8.02031 11.872 8.0032 11.8473 7.995 11.8192L5.005 1.18083C4.9968 1.15271 4.97969 1.128 4.95625 1.11042C4.93281 1.09284 4.9043 1.08333 4.875 1.08333C4.8457 1.08333 4.81719 1.09284 4.79375 1.11042C4.77031 1.128 4.7532 1.15271 4.745 1.18083L3.47208 5.70917C3.40842 5.93621 3.27241 6.13628 3.08472 6.27901C2.89702 6.42173 2.66788 6.49933 2.43208 6.5H1.08333"
        stroke={color}
        strokeWidth={1.08333}
        strokeLinecap="round"
        strokeLinejoin="round"
      />
    </svg>
  );
}

export function HomeIcon({ size = 20, color = "currentColor" }) {
  return (
    <svg width={size} height={size} viewBox="0 0 24 24" fill="none">
      <path
        d="M4 11.5 12 4l8 7.5"
        stroke={color}
        strokeWidth={1.7}
        strokeLinecap="round"
        strokeLinejoin="round"
      />
      <path
        d="M6 10v9a1 1 0 0 0 1 1h3v-5.5a2 2 0 0 1 2-2 2 2 0 0 1 2 2V20h3a1 1 0 0 0 1-1v-9"
        stroke={color}
        strokeWidth={1.7}
        strokeLinecap="round"
        strokeLinejoin="round"
      />
    </svg>
  );
}

export function CalendarIcon({ size = 20, color = "currentColor" }) {
  return (
    <svg width={size} height={size} viewBox="0 0 24 24" fill="none">
      <rect
        x="4"
        y="5.5"
        width="16"
        height="15"
        rx="3"
        stroke={color}
        strokeWidth={1.7}
      />
      <path
        d="M4 10h16M8 3.5v3M16 3.5v3"
        stroke={color}
        strokeWidth={1.7}
        strokeLinecap="round"
      />
    </svg>
  );
}

export function ProfileIcon({ size = 20, color = "currentColor" }) {
  return (
    <svg width={size} height={size} viewBox="0 0 24 24" fill="none">
      <circle cx="12" cy="8.5" r="3.5" stroke={color} strokeWidth={1.7} />
      <path
        d="M5 20c1.2-4 4.2-6 7-6s5.8 2 7 6"
        stroke={color}
        strokeWidth={1.7}
        strokeLinecap="round"
      />
    </svg>
  );
}

export function CloudIcon({ size = 13.5, color = "#1E1E1E" }) {
  return (
    <svg width={size} height={size * (10.375 / 13.5)} viewBox="0 0 13.5 10.375" fill="none">
      <path
        d="M3 9.875C1.61929 9.875 0.5 8.75571 0.5 7.375C0.5 6.20985 1.29707 5.23087 2.37569 4.95358C2.37523 4.92744 2.375 4.90125 2.375 4.875C2.375 2.45875 4.33375 0.5 6.75 0.5C9.00616 0.5 10.8634 2.20781 11.0996 4.40121C12.2052 4.78006 13 5.82847 13 7.0625C13 8.6158 11.7408 9.875 10.1875 9.875C7.85056 9.875 5.61728 9.875 3 9.875Z"
        stroke={color}
        strokeLinecap="round"
        strokeLinejoin="round"
      />
    </svg>
  );
}

export function RainIcon({ size = 12, color = "#1E1E1E" }) {
  return (
    <svg width={size} height={size * (11.9999 / 12)} viewBox="0 0 12 11.9999" fill="none">
      <path
        d="M8.00295 6.49986V10.4999M4.00295 6.49986V10.4999M6.00295 7.49986V11.4999M10.0029 8.28986C10.5286 8.05965 10.959 7.65564 11.222 7.14563C11.485 6.63562 11.5645 6.05066 11.4472 5.48895C11.33 4.92724 11.023 4.42296 10.578 4.06077C10.1329 3.69859 9.57677 3.50053 9.00295 3.49986H8.37295C8.21446 2.88612 7.91237 2.31883 7.4916 1.84476C7.07083 1.37068 6.54342 1.0034 5.95283 0.773168C5.36225 0.54294 4.7254 0.456365 4.09479 0.520579C3.46417 0.584792 2.85785 0.797955 2.32579 1.1425C1.79374 1.48704 1.35118 1.9531 1.0346 2.50226C0.718019 3.05141 0.536483 3.66794 0.504952 4.30103C0.473422 4.93412 0.592801 5.56564 0.853248 6.14353C1.1137 6.72143 1.50776 7.22915 2.00295 7.62486"
        stroke={color}
        strokeLinecap="round"
        strokeLinejoin="round"
      />
    </svg>
  );
}

export function SunIcon({ size = 13.83, color = "#1E1E1E" }) {
  return (
    <svg width={size} height={size} viewBox="0 0 13.8333 13.8333" fill="none">
      <path
        d="M6.91667 0.5V1.66667M6.91667 12.1667V13.3333M2.37833 2.37833L3.20667 3.20667M10.6267 10.6267L11.455 11.455M0.5 6.91667H1.66667M12.1667 6.91667H13.3333M2.37833 11.455L3.20667 10.6267M10.6267 3.20667L11.455 2.37833M9.83333 6.91667C9.83333 8.5275 8.5275 9.83333 6.91667 9.83333C5.30584 9.83333 4 8.5275 4 6.91667C4 5.30584 5.30584 4 6.91667 4C8.5275 4 9.83333 5.30584 9.83333 6.91667Z"
        stroke={color}
        strokeLinecap="round"
        strokeLinejoin="round"
      />
    </svg>
  );
}

export function FlowerIcon({ size = 32, color = "#7958C8", petals = 6 }) {
  const angles = Array.from({ length: petals }, (_, i) => (360 / petals) * i);
  return (
    <svg width={size} height={size} viewBox="0 0 32 32">
      {angles.map((angle) => (
        <ellipse
          key={angle}
          cx="16"
          cy="9.4"
          rx="5.4"
          ry="7.2"
          fill={color}
          opacity={0.92}
          transform={`rotate(${angle} 16 16)`}
        />
      ))}
      <circle cx="16" cy="16" r="4.2" fill="#fffcf6" />
    </svg>
  );
}

export function SproutIcon({ size = 20, color = "#c7c2ce" }) {
  return (
    <svg width={size} height={size} viewBox="0 0 20 20" fill="none">
      <path d="M10 18V9.5" stroke={color} strokeWidth={1.3} strokeLinecap="round" />
      <path
        d="M10 10c-.6-3.4-3.4-4.6-6-4-.2 3.4 2.4 5.6 6 4.6"
        stroke={color}
        strokeWidth={1.3}
        strokeLinecap="round"
        strokeLinejoin="round"
      />
    </svg>
  );
}

export function ChevronLeftIcon({ size = 16, color = "currentColor" }) {
  return (
    <svg width={size} height={size} viewBox="0 0 24 24" fill="none">
      <path
        d="M15 5l-7 7 7 7"
        stroke={color}
        strokeWidth={2}
        strokeLinecap="round"
        strokeLinejoin="round"
      />
    </svg>
  );
}

export function ChevronRightIcon({ size = 16, color = "currentColor" }) {
  return (
    <svg width={size} height={size} viewBox="0 0 24 24" fill="none">
      <path
        d="M9 5l7 7-7 7"
        stroke={color}
        strokeWidth={2}
        strokeLinecap="round"
        strokeLinejoin="round"
      />
    </svg>
  );
}

export function BellIcon({ size = 17, color = "currentColor" }) {
  return (
    <svg width={size} height={size} viewBox="0 0 24 24" fill="none">
      <path
        d="M6 10a6 6 0 1 1 12 0c0 3.2 1 5 2 6H4c1-1 2-2.8 2-6Z"
        stroke={color}
        strokeWidth={1.6}
        strokeLinecap="round"
        strokeLinejoin="round"
      />
      <path d="M10 19a2 2 0 0 0 4 0" stroke={color} strokeWidth={1.6} strokeLinecap="round" />
    </svg>
  );
}

export function ClockIcon({ size = 17, color = "currentColor" }) {
  return (
    <svg width={size} height={size} viewBox="0 0 24 24" fill="none">
      <circle cx="12" cy="12" r="9" stroke={color} strokeWidth={1.6} />
      <path
        d="M12 7v5l3.5 2"
        stroke={color}
        strokeWidth={1.6}
        strokeLinecap="round"
        strokeLinejoin="round"
      />
    </svg>
  );
}

export function ShieldIcon({ size = 17, color = "currentColor" }) {
  return (
    <svg width={size} height={size} viewBox="0 0 24 24" fill="none">
      <path
        d="M12 3l7 3v6c0 4.5-3 7.5-7 9-4-1.5-7-4.5-7-9V6l7-3Z"
        stroke={color}
        strokeWidth={1.6}
        strokeLinejoin="round"
      />
    </svg>
  );
}

export function GlobeIcon({ size = 17, color = "currentColor" }) {
  return (
    <svg width={size} height={size} viewBox="0 0 24 24" fill="none">
      <circle cx="12" cy="12" r="9" stroke={color} strokeWidth={1.6} />
      <path
        d="M3 12h18M12 3c2.5 2.5 4 5.7 4 9s-1.5 6.5-4 9c-2.5-2.5-4-5.7-4-9s1.5-6.5 4-9Z"
        stroke={color}
        strokeWidth={1.6}
      />
    </svg>
  );
}

export function HelpCircleIcon({ size = 17, color = "currentColor" }) {
  return (
    <svg width={size} height={size} viewBox="0 0 24 24" fill="none">
      <circle cx="12" cy="12" r="9" stroke={color} strokeWidth={1.6} />
      <path
        d="M9.5 9.2a2.5 2.5 0 1 1 3.7 2.2c-.9.5-1.2 1-1.2 2"
        stroke={color}
        strokeWidth={1.6}
        strokeLinecap="round"
      />
      <circle cx="12" cy="17" r="1" fill={color} />
    </svg>
  );
}

export function LogOutIcon({ size = 16, color = "currentColor" }) {
  return (
    <svg width={size} height={size} viewBox="0 0 24 24" fill="none">
      <path
        d="M9 21H5a2 2 0 0 1-2-2V5a2 2 0 0 1 2-2h4"
        stroke={color}
        strokeWidth={1.6}
        strokeLinecap="round"
        strokeLinejoin="round"
      />
      <path
        d="M16 17l5-5-5-5M21 12H9"
        stroke={color}
        strokeWidth={1.6}
        strokeLinecap="round"
        strokeLinejoin="round"
      />
    </svg>
  );
}

const MOOD_MOUTHS = {
  down: "M9 16c1-1.5 5-1.5 6 0",
  low: "M9 15.3c1-.6 5-.6 6 0",
  neutral: "M9 15h6",
  happy: "M8.5 14.5c1.2 1.6 5.8 1.6 7 0",
};

export function MoodFaceIcon({
  size = 24,
  color = "currentColor",
  variant = "neutral",
}) {
  return (
    <svg width={size} height={size} viewBox="0 0 24 24" fill="none">
      <circle cx="12" cy="12" r="9.5" stroke={color} strokeWidth={1.5} />
      <circle cx="9" cy="10" r="1" fill={color} />
      <circle cx="15" cy="10" r="1" fill={color} />
      <path
        d={MOOD_MOUTHS[variant]}
        stroke={color}
        strokeWidth={1.5}
        strokeLinecap="round"
      />
    </svg>
  );
}
