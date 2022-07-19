# xtianikov's build of dwm
This is my custom build of the suckless window manager.

This particular build is meant to be used in conjunction with the other suckless programs. This includes st, dmenu, and one of the user-created builds of dwmblocks.

# Patches
- actualfullscreen
- alpha
- alwayscenter
- cool-autostart
- cyclelayouts
- hide_vacant_tags
- movestack
- pertag
- removeborder
- restartsig
- statuscmd
- swallow
- vanitygaps

# Requirements
1. Install **libxft-bgra** from the AUR - since this build uses colored emojis and dwm (unpatched) doesn't allow this.
2. The following fonts: (or you can just change the fonts in the **config.h** file to what you have)
   1. Liberation Mono
   2. Jetbrains Mono
   3. Noto Color Emoji
3. My dotfiles repo - most of the scripts I use with dwm keybindings are there. (*this is optional*)
