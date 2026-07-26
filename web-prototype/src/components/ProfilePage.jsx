import { ProfileIcon } from "./icons";

export default function ProfilePage() {
  return (
    <div className="stub-page">
      <div className="stub-page__icon">
        <ProfileIcon size={28} color="var(--color-primary)" />
      </div>
      <h2>我的</h2>
      <p>个人信息与设备设置会在这里出现，敬请期待。</p>
    </div>
  );
}
