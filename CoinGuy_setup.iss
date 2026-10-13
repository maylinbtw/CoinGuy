[Setup]
AppName=CoinGuy
AppVersion=1.0
DefaultDirName={autopf}\CoinGuy
DefaultGroupName=CoinGuy
OutputDir=C:\Users\User\source\repos\CoinGuy\Installer
OutputBaseFilename=CoinGuy_Setup
Compression=lzma
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"

[Files]
Source: "C:\Users\User\source\repos\CoinGuy\x64\Debug\CoinGuy.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\User\source\repos\CoinGuy\x64\Debug\assets\*"; DestDir: "{app}\assets"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:\Users\User\source\repos\CoinGuy\x64\Debug\*.dll"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\CoinGuy"; Filename: "{app}\CoinGuy.exe"
Name: "{group}\{cm:UninstallProgram,CoinGuy}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\CoinGuy"; Filename: "{app}\CoinGuy.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\CoinGuy.exe"; Description: "{cm:LaunchProgram,CoinGuy}"; Flags: nowait postinstall skipifsilent
