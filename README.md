
# Usage

First, make sure the python dependencies are installed:

```
pip install -r requirements.txt
```

Next, we will use `cookiecutter` and Jolt's cookiecutter app template to 
generate a jolt application project.

```
cookiecutter https://github.com/joltwallet/cookiecutter-joltapp
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


# TODO

* Replace dummy default `app_key` with real public key
*
