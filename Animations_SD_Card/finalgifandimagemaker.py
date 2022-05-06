
##README: If you want to write an image, use img2txt(image_filename, output textfile filename). Jpegs and pngs should both work. If you want to write a gif, use gif2txt(gif filename, output textfile filename). output filename has to have .txt cause i don't have it in me to format any more strings than I already have
#If you have several gifs and images you want to do at the same time, put use handle_batch(folder with files to convert, folder where you want to store the outputs,gifmode=mode you want to convert gifs with (optional),imgmode=mode you want to convert static images with (optional)). Note that you don't get to name files individually this way - whatever you name the original file will be used (with static or ani to denote if it's a static gif or animation). Transparent pixels get turned to black (which translates to the LEDs on the strips being just off); nonsquare gifs will get auto-resized so they'll probably either look really ugly or just not work, so you should resize them before use
#If it runs into an error transcribing the image, it will delete the txt file it made to avoid any issues on the actual system (can't imagine why this would happen though)
from PIL import Image
from PIL import ImageFile
import PIL
import numpy
import sys
import os


ImageFile.LOAD_TRUNCATED_IMAGES = True

def expand2square(pil_img, background_color):
    width, height = pil_img.size
    if width == height:
        return pil_img
    elif width > height:
        result = Image.new(pil_img.mode, (width, width), background_color)
        result.paste(pil_img, (0, (width - height) // 2))
        return result
    else:
        result = Image.new(pil_img.mode, (height, height), background_color)
        result.paste(pil_img, ((height - width) // 2, 0))
        return result

def resize_image(image, filename="", autosave=True, image_mode=Image.Resampling.NEAREST):
    height = image.height
    width = image.width
    resized=image.resize((32,32), image_mode)
    if autosave:
        resized.save(filename)
    return resized

def write_image_text(image, filename, printO=False, fix=True, autoclose=True, filemode='w'):
    #image=expand2square(pre_image, (255,255,255))
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
    delay=min(gif.info.get('duration'),100)
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
    print("All done with "+input_file+"!")

def gif2txt(input_file, output_file, image_mode=Image.Resampling.LANCZOS, printO=False):
    write_gif_text(Image.open(input_file), output_file, image_mode=image_mode, printO=printO)
    print("All done with "+input_file+"!")

def handle_batch(input_folder, output_folder, gifmode=Image.Resampling.LANCZOS, imgmode=Image.Resampling.NEAREST, printO=False):
    files=os.listdir(input_folder)
    files_to_kill=[]
    for filename in files:
        try:
            name=filename.split('.')[0]
            extension=filename.split('.')[1]
            if extension=="gif":
                gif2txt(input_folder+"/"+filename, output_folder+"/"+name+"-ani.txt", image_mode=gifmode, printO=printO)
            elif extension=="png" or extension=="jpg":
                image2txt(input_folder+"/"+filename, output_folder+"/"+name+"-static.txt", image_mode=imgmode, printO=printO)
            else:
                print("Unsupported filetype for file "+filename)
        except UnicodeEncodeError as uee:
            print(uee)
            if extension=="gif":
                files_to_kill.append(output_folder+"/"+name+"-ani.txt")
            else:
                files_to_kill.append(output_folder+"/"+name+"-static.txt")
            continue
    for k in files_to_kill:
        os.remove(k)


#gif2txt("batches/earthspin.gif", "finaltxts/earthspin-ani.txt", image_mode=Image.Resampling.NEAREST)
#image2txt("batches/sparklogo.jpg","finaltxts/sparklogo-static.txt", image_mode=Image.Resampling.BICUBIC)
handle_batch("batches","finaltxts", gifmode=Image.Resampling.BOX, imgmode=Image.Resampling.LANCZOS)
