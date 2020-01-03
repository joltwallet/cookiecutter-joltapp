
# Usage

First, make sure the python dependencies are installed:

```
pip install -r requirements.txt
```

Next, we will use `cookiecutter` and Jolt's cookiecutter app template to 
generate a jolt application project.

```
cookiecutter -c v0.1.1 https://github.com/joltwallet/cookiecutter-joltapp
```

Follow the onscreen prompts; pressing enter will use the default value.
The prompts are described in more detail as below.

1. `app_name` - Name of the app *exactly* as it should appear on device. Case-sensitive.
2. `app_var_name` - Name of app-related variables in code.
3. `folder_name` - name of the folder to contain the project.
4. `signing_key` - private key to sign your application with. Using the default
                   key here is fine since Jolt will have to sign it with the 
                   master private key upon release.
5. `coin_path` - The registered [coin type](https://github.com/satoshilabs/slips/blob/master/slip-0044.md) for the coin.
6. `bip32_key` - The derivation seed string. Typically `Bitcoin seed` or `ed25519 seed`


# Features

This cookiecutter performs the following actions or sets up to allow you to perform
the following actions:

## Git

Git will be initialized and all the files will be commited indicating 
the cookiecutter version and commit you used.

Build artifacts will already be in the `.gitignore`

## Build system

The Makefile will already be populated so that you can immediately build your
application. See your app's README for more information.

ESP-IDF style components can be added to the `components` directory and will
automatically be detected by the build system.

## Versioning

Use `bumpversion` to manage your app's version.

```
pip3 install bumpversion
```

This template already has a `.bumpversion.cfg` populated for you. In your project's
clean (no unstaged changes) root directory, the following commands will increase
the version number and commit the version change:

```
bumpversion major  # For backwards incompatible changes.
bumpversion minor  # For backwards compatible feature updates
bumpversion patch  # For bug fixes
```
