
#ifdef HAS_ETHERNET

#include "ETH.h"
#include "ESPEasy-Globals.h"

bool ethUseStaticIP() {
  return Settings.ETH_IP[0] != 0 && Settings.ETH_IP[3] != 255;
}

void ethSetupStaticIPconfig() {
  // TODO: PKR Remove
  addLog(LOG_LEVEL_INFO, F("ethSetupStaticIPConfig Started"));
  //setUseStaticIP(useStaticIP());

  if (!ethUseStaticIP()) { return; }
  const IPAddress ip     = Settings.ETH_IP;
  const IPAddress gw     = Settings.ETH_Gateway;
  const IPAddress subnet = Settings.ETH_Subnet;
  const IPAddress dns    = Settings.ETH_DNS;

  if (loglevelActiveFor(LOG_LEVEL_INFO)) {
    String log = F("ETH IP   : Static IP : ");
    log += formatIP(ip);
    log += F(" GW: ");
    log += formatIP(gw);
    log += F(" SN: ");
    log += formatIP(subnet);
    log += F(" DNS: ");
    log += formatIP(dns);
    addLog(LOG_LEVEL_INFO, log);
  }
  // TODO: PKR Remove
  addLog(LOG_LEVEL_INFO, F("Before ETH.config"));
  ETH.config(ip, gw, subnet, dns);
  // TODO: PKR Remove
  addLog(LOG_LEVEL_INFO, F("After ETH.config"));
}

bool ethCheckSettings() {
  // TODO: PKR Remove
  addLog(LOG_LEVEL_INFO, F("ethCheckSettings Started"));
  bool result = true;
  if (Settings.ETH_Phy_Type != 0 && Settings.ETH_Phy_Type != 1)
    result = false;
  if (Settings.ETH_Clock_Mode > 3)
    result = false;
  if (Settings.ETH_Wifi_Mode > 1)
    result = false;
  if (Settings.ETH_Pin_mdc > MAX_GPIO)
    result = false;
  if (Settings.ETH_Pin_mdio > MAX_GPIO)
    result = false;
  if (Settings.ETH_Pin_power > MAX_GPIO)
    result = false;
  return result;
}

bool ethPrepare() {
  // TODO: PKR Remove
  addLog(LOG_LEVEL_INFO, F("ethPrepare Started"));
  if (!ethCheckSettings())
  {
    addLog(LOG_LEVEL_ERROR, F("ETH: Settings not correct!!!"));
    return false;
  }
  // TODO: PKR Remove
  addLog(LOG_LEVEL_INFO, F("Before ETH.config"));
  ETH.config(INADDR_NONE, INADDR_NONE, INADDR_NONE);
  // TODO: PKR Remove
  addLog(LOG_LEVEL_INFO, F("After ETH.conif"));
  ethSetupStaticIPconfig();
  return true;
}

String ethGetDebugClockModeStr() {
  // TODO: PKR Remove
  addLog(LOG_LEVEL_INFO, F("ethDebugColckModeStr Started"));
  switch (Settings.ETH_Clock_Mode)
  {
    case 0: return F("ETH_CLOCK_GPIO0_IN");
    case 1: return F("ETH_CLOCK_GPIO0_OUT");
    case 2: return F("ETH_CLOCK_GPIO16_OUT");
    case 3: return F("ETH_CLOCK_GPIO17_OUT");
    default: return F("ETH_CLOCK_ERR");
  }
}

String ethGetDebugEthWifiModeStr() {
  // TODO: PKR Remove
  addLog(LOG_LEVEL_INFO, F("ethGetDebugEthWifiMode Started"));
  switch (eth_wifi_mode)
  {
    case 0: return F("WIFI");
    case 1: return F("ETHERNET");
    default: return F("ETH_WIFI_ERR");
  }
}

void ethPrintSettings() {
  // TODO: PKR Remove
  addLog(LOG_LEVEL_INFO, F("ethPrintSettings Started"));
  String settingsDebugLog;
  settingsDebugLog.reserve(115);
  settingsDebugLog += F("Eth Wifi mode: ");
  settingsDebugLog += ethGetDebugEthWifiModeStr();
  settingsDebugLog += F(" ETH: PHY Type: ");
  settingsDebugLog += Settings.ETH_Phy_Type == 0 ? F("ETH_PHY_LAN8720") : F("ETH_PHY_TLK110");
  settingsDebugLog += F(" PHY Addr: ");
  settingsDebugLog += Settings.ETH_Phy_Addr;
  settingsDebugLog += F(" Eth Clock mode: ");
  settingsDebugLog += ethGetDebugClockModeStr();
  settingsDebugLog += F(" MDC Pin: ");
  settingsDebugLog += String(Settings.ETH_Pin_mdc);
  settingsDebugLog += F(" MIO Pin: ");
  settingsDebugLog += String(Settings.ETH_Pin_mdio);
  settingsDebugLog += F(" Power Pin: ");
  settingsDebugLog += String(Settings.ETH_Pin_power);
  addLog(LOG_LEVEL_INFO, settingsDebugLog);
}

void ETHConnectRelaxed() {
  // TODO: PKR Remove
  addLog(LOG_LEVEL_INFO, F("ETHConnectRelaxed Started"));
  ethPrintSettings();
  /*if (!ethPrepare()) {
    // Dead code for now...
    addLog(LOG_LEVEL_ERROR, F("ETH : Could not prepare ETH!"));
    return;
  }
  // TODO: PKR Remove
  addLog(LOG_LEVEL_INFO, F("Before ETH.begin"));
  ETH.begin(Settings.ETH_Phy_Addr,
            Settings.ETH_Pin_power,
            Settings.ETH_Pin_mdc,
            Settings.ETH_Pin_mdio,
            (eth_phy_type_t)Settings.ETH_Phy_Type,
            (eth_clock_mode_t)Settings.ETH_Clock_Mode);
  // TODO: PKR Remove*/
  ETH.begin();
  addLog(LOG_LEVEL_INFO, F("After ETH.begin"));
}

bool ETHConnected() {
  return eth_connected;
}

#endif