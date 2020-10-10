# Script to create the desired icons on the fly
# using the original icons of the supplied icon pack

import numpy as np
import pathlib
from PIL import Image, ImageDraw, ImageOps

original_paths = pathlib.Path('media/orig/').glob('*.png')

options = {
    'size': (40, 40),
    'background': (0, 0, 0, 255),
    'shadow':     (50, 50, 50, 255),
    'foreground': (150, 150, 150, 255),
}

for original_file in original_paths:

    icon_alpha  = Image.open(original_file).split()[-1]
    shadow_dx = -10
    shadow_dy = -5
    transform_tuple = (1, 0, shadow_dx, 0, 1, shadow_dy)
    icon_shadow = icon_alpha.transform(icon_alpha.size, Image.AFFINE, transform_tuple)

    foreground = Image.new('RGBA', icon_alpha.size, options['foreground'])
    shadow     = Image.new('RGBA', icon_alpha.size, options['shadow'])
    composite  = Image.new('RGBA', icon_alpha.size, options['background'])

    composite.paste(shadow, mask=icon_shadow)
    composite.paste(foreground, mask=icon_alpha)
    composite = composite.convert('RGB').resize(options['size'], Image.LANCZOS)

    composite.save(f'media/icon-{original_file.stem}.png')


