# x1nigo's build of dwm
This is my custom build of the suckless window manager.

This particular build is meant to be used in conjunction with the other suckless programs. This includes st, dmenu, and one of the user-created builds of dwmblocks.

## Patches
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

## Requirements
- ***libxft-bgra*** from the AUR - since this build uses colored emojis and dwm (unpatched) doesn't allow this.

## Keybindings
I'm not going to list every single keybinding I have. If you want to know more, just examine my `config.h` file.
| Keys | Action |
|------|--------|
| <kbd>Mod</kbd> + <kbd>Return</kbd> | terminal (st) |
| <kbd>Mod</kbd> + <kbd>p</kbd> | dmenu |
| <kbd>Mod</kbd> + <kbd>b</kbd> | browser |
| <kbd>Mod</kbd> + <kbd>q</kbd> | system menu |
| <kbd>Mod</kbd> + <kbd>Shift</kbd> + <kbd>s</kbd> | take a screenshot |

## References
- For the original version, see http://dwm.suckless.org/.
