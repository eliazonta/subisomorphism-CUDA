import os
import urllib.request
from pathlib import Path
import shutil
import gzip

BASE_DIR = Path(__file__).resolve().parent.parent

DATA_DIR = BASE_DIR / "data/" # directory where the datasets will be stored
TEMP_DIR = BASE_DIR / ".temp/" # directory where the datasets will be downloaded

# datasets to download
DATASETS_URLS = {
    "enron": {
        "url": "https://snap.stanford.edu/data/email-Enron.txt.gz",
        "filename": "enron.txt.gz",
    },
    "gowalla": {
        "url": "https://snap.stanford.edu/data/loc-gowalla_edges.txt.gz",
        "filename": "gowalla.txt.gz",
    },
    "patent": {
        "url": "https://snap.stanford.edu/data/cit-Patents.txt.gz",
        "filename": "patent.txt.gz",
    },
    "road_california": {
        "url": "https://snap.stanford.edu/data/roadNet-CA.txt.gz",
        "filename": "road_california.txt.gz",
    },
}

def download_progress(count, block_size, total_size):
    downloaded_size = count * block_size
    total_size_mb = int(round(total_size / (1024 * 1024), 2))
    downloaded_size_mb = int(round(downloaded_size / (1024 * 1024), 2))
    print(f"Progress: {downloaded_size_mb}/{total_size_mb}MB\t\t", end="\r")

if __name__ == "__main__":
    """
    Download datasets and extract them into the data directory.
    """
    
    # prepare directories
    DATA_DIR.mkdir(exist_ok=True)
    TEMP_DIR.mkdir(exist_ok=True)

    def extract_or_move(filename):
        if filename.endswith(".tar.gz"):
            print(f"Extracting {filename} into {DATA_DIR}")
            shutil.unpack_archive(DATA_DIR / filename, DATA_DIR)
        elif filename.endswith(".gz"):
            print(f"Extracting {filename} into {DATA_DIR}")
            with gzip.open(TEMP_DIR / filename, "rb") as f_in:
                with open(DATA_DIR / filename[:-3], "wb") as f_out:
                    shutil.copyfileobj(f_in, f_out)
        else:
            shutil.move(TEMP_DIR / filename, DATA_DIR / filename)

    for i, (dataset_name, dataset) in enumerate(DATASETS_URLS.items()):
        url = dataset["url"]
        filename = dataset["filename"]
        print(f"{i}) {dataset_name}")
        if (TEMP_DIR / filename).exists():
            if not Path(filename).stem in os.listdir(DATA_DIR):
                extract_or_move(filename)
        else:
            print(f"Downloading {dataset_name} dataset from {url} into {TEMP_DIR}")
            urllib.request.urlretrieve(url, TEMP_DIR / filename, reporthook=download_progress)
            print()
            extract_or_move(filename)