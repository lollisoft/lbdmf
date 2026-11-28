# lbDMF — Distributed Multiplatform Framework

**Copyright © 2000–2026 Lothar Behrens**

[![build result](https://build.opensuse.org/projects/home:lollisoft/packages/lbdmf-obs/badge.svg?type=default)](https://build.opensuse.org/package/show/home:lollisoft/lbdmf-obs)

> **Overview:** lbDMF is a cross-platform C++ framework built on wxWidgets. This concise README is tailored for GitHub to help you build, test, and contribute quickly.

---

## Need support for Code Signing

DMF has been free and open source since 2003. To renew the annual Code Signing certificate (~30 €) to avoid SmartScreen warnings, small contributions via PayPal https://www.paypal.me/LotharBehrens63150 are greatly appreciated!

Currently I cannot afford the signing, so only the Mac OS X release and the openSuSE Tumbleweed releases are signed for now.

For the OBS build, the public key could be imported at https://download.opensuse.org/repositories/home:/lollisoft/openSUSE_Tumbleweed/repodata/repomd.xml.key

Thank you very much!  
Lothar Behrens

---

## 💬 Contact & Community

For a chat beside a bugreport or issues, you also can contact me on [Discord](https://discord.gg/JbN4zTf3am). There I provide some direct chat option that I may notice on my mobile phone.

---

## ⚠️  Repository & Sync Notice

This Git repository is incrementally synced from a legacy **CVS repository** and may occasionally undergo a full resync if an incremental update fails.

* **Why CVS is still used:** The legacy CVS setup drives an older Jenkins instance with a **Windows XP build agent** to maintain production 16-bit and legacy components for the sake of porting effords. It also still exists a working Mac mini G4 and thus still a PPC Leopard based release and respectively a jenkins job. That is supported as long as the box is working. That is also a reason for sticking to Jenkins ver. 1.576 as a version that slaves can support that old G4.
* **Project Roadmap:** Porting these legacy codebases to modern platforms is an ongoing primary goal.
* **Pull Requests & Forks:** A full resync may disconnect existing forks; please re-fork or reparent your fork before submitting a pull request.

---

## 🚀 Quick Installation & Setup

### Windows
1. Download the source code installer from [Sourceforge](https://sourceforge.net/projects/lbdmf/files/lbdmf/lbDMF-1.3.5/lbDMF-Source-1.3.5.exe/download).
2. Run the installer and select **only one** of the following build environments to avoid conflicts:
   * `Get MinGW, wxWidgets (and ACE when flagged) and build it with debug`
   * `Get MinGW64, wxWidgets (and ACE when flagged) and build it with debug`
4. Follow the automated batch script prompts to install compiler and build dependencies.
5. After `wxWidgets` finishes compiling, close the command prompt and open the **`lbDMF Develop`** desktop shortcut, then run:
   ```cmd
   make
   wxWrapper
   ```
   *(Type `make` in the build directory, and then type `wxWrapper` once ready).*

---

### Linux

You can either build `lbDMF` directly from the GitHub source code or test pre-built `.rpm` packages using Podman.

#### 1. Building from Source (GitHub)
1. Clone the repository into your development workspace:
   ```bash
   git clone https://github.com/lollisoft/lbdmf.git ~/develop/Projects/lbdmf
   ```
2. Configure the required environment variables *(TBD — exact Linux profile variables to be documented)*:
   ```bash
   # Placeholder: Add required DEVROOT, LD_LIBRARY_PATH, and PLUGIN_DIR exports here
   ```
3. Compile and launch the framework:
   ```bash
   cd ~/develop/Projects/lbdmf/BaseDevelopment
   make
   wxWrapper
   ```

#### 2. Testing on openSUSE Tumbleweed via Podman (Windows 10 Host)
If you are on a Windows 10 host, you can test `.rpm` installations using the provided helper batch scripts (requires a standard Podman setup and a `D:` drive for image storage):
* **`InitialSetup.bat`** — Configures a minimal environment on a clean machine.
* **`Test-lbdmf-Tumbleweed.bat`** — Spins up a minimal openSUSE Tumbleweed image, installs the `.rpm` package, and lets you test by running `wxWrapper`.
* **`DropSetup.bat`** — Cleans up and removes temporary Podman image folders from your `D:` drive.

---

### macOS (OS X)
1. Clone the repository into `~/develop/Projects` so `DEVROOT` resolves properly.
2. Add the environment configuration to your user profile (`~/.zshrc` or `~/.bash_profile`), ensuring proper path and shell expansions for `DEVROOT`, `OSVERSION` (`uname -r`), and `OSPLATFORM` (`uname -p`).

---

## 🤝 Contributing

Bug reports, testing feedback (via Tumbleweed Podman scripts), and porting assistance are welcome. Review the **Repository & Sync Notice** prior to opening pull requests. I would appreciate any help beside code suggestions or patches. If you fork and provide a pull request, I have to learn to cope with that but also need some extra work to take that over to my internal master CVS repository. Any contribution will mention it's contributor. Btw, please do not try to suggest code modernization. I need strictly a backward compatibility down to Watcom 11 or Power++ 2.1 Enterprise and Visual C++ 6.0. My porting effords need a working code base I can use on an old XP VM installation - see above (Repository & Sync Notice).
