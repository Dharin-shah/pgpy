# pgpy
Postgres extension to run python ML models directly on DB server

## Development (Mac & Postgres 15)
Install postgres

>  brew install postgresql@15

Setup env 
> export PATH="/opt/homebrew/opt/postgresql@15/bin:$PATH"; 
> export PKG_CONFIG_PATH="/opt/homebrew/opt/postgresql@15/lib/pkgconfig"

Setup Libs

> export CPPFLAGS="-I/opt/homebrew/opt/postgresql@15/include";
> export LDFLAGS="-L/opt/homebrew/opt/postgresql@15/lib" 

Build

> make clean && --preserve-env=PG_CONFIG make install

