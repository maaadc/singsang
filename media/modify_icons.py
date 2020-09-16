# Script to create the desired icons on the fly
# using the original icons of the supplied icon pack

import pathlib
from PIL import Image, ImageDraw, ImageOps

original_paths = pathlib.Path('media/orig/').glob('*.png')

options = {
    'size': (40, 40),
    'background': (0, 0, 0, 255),
    'foreground': (100, 100, 100, 255),
}

for original_file in original_paths:

    icon_alpha = Image.open(original_file).split()[-1]

    foreground = Image.new('RGBA', icon_alpha.size, options['foreground'])
    composite = Image.new('RGBA', icon_alpha.size, options['background'])

    composite.paste(foreground, mask=icon_alpha)
    composite = composite.convert('RGB').resize(options['size'], Image.LANCZOS)

    composite.save(f'media/icon-{original_file.stem}.png')


