function polarToCartesian(cx, cy, r, angleDeg) {
  const rad = ((angleDeg - 90) * Math.PI) / 180;
  return {
    x: cx + r * Math.cos(rad),
    y: cy + r * Math.sin(rad),
  };
}

function describeArc(cx, cy, r, startAngle, endAngle) {
  const start = polarToCartesian(cx, cy, r, endAngle);
  const end = polarToCartesian(cx, cy, r, startAngle);
  const largeArcFlag = endAngle - startAngle <= 180 ? "0" : "1";
  return `M ${start.x} ${start.y} A ${r} ${r} 0 ${largeArcFlag} 0 ${end.x} ${end.y}`;
}

export default function CycleRing({
  cycleDay = 8,
  cycleLength = 28,
  size = 260,
  children,
}) {
  const center = size / 2;
  const radius = size / 2 - 12;
  const progressAngle = (cycleDay / cycleLength) * 360;
  const dot = polarToCartesian(center, center, radius, progressAngle);

  return (
    <div className="cycle-ring" style={{ width: size, height: size }}>
      <svg
        width={size}
        height={size}
        viewBox={`0 0 ${size} ${size}`}
        className="cycle-ring__svg"
      >
        <circle
          cx={center}
          cy={center}
          r={radius}
          fill="none"
          stroke="var(--color-primary-soft)"
          strokeWidth={1.5}
        />
        <path
          d={describeArc(center, center, radius, -14, 14)}
          fill="none"
          stroke="var(--color-primary)"
          strokeWidth={2.5}
          strokeLinecap="round"
        />
        <path
          d={describeArc(center, center, radius, 166, 194)}
          fill="none"
          stroke="var(--color-primary)"
          strokeWidth={2.5}
          strokeLinecap="round"
        />
        <circle cx={dot.x} cy={dot.y} r={5} fill="var(--color-primary)" />
      </svg>
      <div className="cycle-ring__center">{children}</div>
    </div>
  );
}
