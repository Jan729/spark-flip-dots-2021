
##README: If you want to write an image, use img2txt(image_filename, output textfile filename). Jpegs and pngs should both work. If you want to write a gif, use gif2txt(gif filename, output textfile filename). output filename has to have .txt cause i don't have it in me to format any more strings thatn I already have
from PIL import Image
from PIL import ImageFile
import PIL
import numpy
import sys


ImageFile.LOAD_TRUNCATED_IMAGES = True

def resize_image(image, filename="", autosave=True, image_mode=Image.Resampling.NEAREST):
    height = image.height
    width = image.width
    resized=image.resize((32,32), image_mode)
    if autosave:
        resized.save(filename)
    return resized

def write_image_text(image, filename, printO=False, fix=True, autoclose=True, filemode='w'):
    data=numpy.asarray(image)
    f=open(filename, filemode)
    count=0
    #STRIP 11, COLUMN 9,10,11,12
    for row in data:
        for pixel in row:
            if printO:
                print("Location (strip, column): "+str(31-int(count/32))+", "+str(count%32))
            count=count+1
            if len(pixel)>3:
                mult=pixel[3]/255
                if printO:
                    print("Alpha channel:" + str(pixel[3])+"RGB: ")
            else:
                mult=1.0
            for i in range(3):
                col=int(mult*pixel[i]*0.5)
                if fix:
                    if col==13:
                        col=12
                    if col==10:
                        col=9
                if printO:
                    print(col)
                f.write(chr(col))
        #Note to self: have to re-multiply by 2 afterwards, gonna lose some image niceness sadly
        #Alternatively, I could write each colour in two bytes to preserve the image quality and give up on space... to decide on later
    if autoclose:
        f.close()
    #print(count)

def scale_gif(path, scale, new_path=None, image_mode=Image.Resampling.LANCZOS):
    gif = Image.open(path)
    if not new_path:
        new_path = path
    old_gif_information = {
        'loop': bool(gif.info.get('loop', 1)),
        'duration': gif.info.get('duration', 40),
        'background': gif.info.get('background', 223),
        'extension': gif.info.get('extension', (b'NETSCAPE2.0'))
    }
    new_frames = get_new_frames(gif, scale, image_mode=image_mode)
    save_new_gif(new_frames, old_gif_information, new_path)

def get_new_frames(gif, scale, image_mode=Image.Resampling.LANCZOS):
    new_frames = []
    actual_frames = gif.n_frames
    for frame in range(actual_frames):
        gif.seek(frame)
        new_frame = Image.new('RGBA', gif.size)
        new_frame.paste(gif)
        new_frame=new_frame.resize(scale, image_mode)
        new_frames.append(new_frame)
    return new_frames

def save_new_gif(new_frames, old_gif_information, new_path):
    new_frames[0].save(new_path,
                       save_all = True,
                       append_images = new_frames[1:],
                       duration = old_gif_information['duration'],
                       loop = old_gif_information['loop'],
                       background = old_gif_information['background'],
                       extension = old_gif_information['extension'])

def write_gif_text(gif, filename, delay=9, printO=False, fix=True, image_mode=Image.Resampling.LANCZOS):
    new_frames=get_new_frames(gif, (32,32), image_mode=image_mode)
    delay=gif.info.get('duration')
    if delay==13:
        delay=12
    if delay==10:
        delay=9
    if printO:
        print("DELAY: " +str(delay))
    write_image_text(new_frames[0], filename, printO=printO, fix=fix, filemode='w')
    f=open(filename,'a')
    f.write(chr(delay))
    f.close()
    for i in range(1, gif.n_frames):
        write_image_text(new_frames[i], filename, printO=printO, fix=fix, filemode='a')
        f=open(filename,'a')
        f.write(chr(delay))
        f.close()


def image2txt(input_file, output_file, image_mode=Image.Resampling.NEAREST, printO=False):
    resized=resize_image(Image.open(input_file), autosave=False, image_mode=image_mode)
    write_image_text(resized, output_file, printO)
    print("All done!")

def gif2txt(input_file, output_file, image_mode=Image.Resampling.LANCZOS, printO=False):
    write_gif_text(Image.open(input_file), output_file, image_mode=image_mode, printO=printO)
    print("All done!")

# gif2txt("splash_XS_frame_data.gif", "splash_XS_frame_data.txt", image_mode=Image.Resampling.BOX)
gif2txt("splash_xxl_frame_data_filled.gif", "splash_xxl_frame_data_filled.txt", image_mode=Image.Resampling.BOX)
#image2txt("Utoronto_coa.png","finaltxts/utlogo-static.txt", image_mode=Image.Resampling.BOX)
