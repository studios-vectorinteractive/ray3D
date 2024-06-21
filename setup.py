import os
import urllib.request
import zipfile

def download_and_unzip(url, target_dir):
    if not os.path.exists(target_dir):
        os.makedirs(target_dir)

    print("Downlading Premake5...")
    zip_filename = os.path.join(target_dir, "premake5.zip")
    urllib.request.urlretrieve(url, zip_filename)

    with zipfile.ZipFile(zip_filename, 'r') as zip_ref:
        zip_ref.extractall(target_dir)

    os.remove(zip_filename)

if __name__ == "__main__":
    url = "https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip"  # Replace with your actual URL
    target_directory = "ext-bin/"  # Replace with the desired directory path

    download_and_unzip(url, target_directory)
