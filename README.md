# x1nigo's build of dwm
This is my custom build of the suckless window manager.

This particular build is meant to be used in conjunction with the other suckless programs. This includes st, dmenu, and one of the user-created builds of dwmblocks.

## Patches
- `actualfullscreen` (enables fullscreen toggle)
- `alpha` (transparency and fixes weird borders)
- `alwayscenter` (floating windows spawn at the center)
- `cyclelayouts` (keybindings for switching between multiple layouts)
- `hide_vacant_tags` (only show active tags)
- `movestack` (allows moving of windows up/down the stack)
- `pertag` (different layout per tag)
- `removeborder` (removes border for monocle layout)
- `restartsig` (allows dwm to restart its config)
- `restoreafterrestart` (restores tags of windows upon restart &ndash; to be used alongside `restartsig`)
- `statuscmd` (clickable events in status bar)
- `swallow` (window swallowing)
- `vanitygaps` (lots of options for gaps)

## Requirements
- `libxft-bgra` &ndash; since this build uses colored emojis and dwm (unpatched) doesn't allow this.

## References
- For the original version, see http://dwm.suckless.org/.
