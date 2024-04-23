# snip
Stupid utility to easily store code snippets or files in general.

## Usage
```
usage: snip [store <file> <name> | rm <name> | show <name> | get <name> [as] | list]

commands:
  store <file> <name>  Stores the given file with the given name
  rm <name>            Removes the snip
  show <name>          Show the given snip with the user's SNIP_PAGER
  get <name> [as]      Gets the snips contents. If as is not set,
                       it is simply put into stdout. If as is set,
                       it will be put in a new file of the same name.
  list                 List all stored snips
```

## Environment
### SNIP_STORE
The `SNIP_STORE` environment variable tells snip where it should store snips. If
the given directory does not exist it will be created.

### SNIP_PAGER
The program set in the `SNIP_PAGER` environment variable is used by `snip show`
to display the contents of the snip. If not set, snip falls back to the `PAGER`
variable. If this is also not set snip will attempt to use more.
