from PIL import Image, ImageDraw, ImageFont

def processimage():
        im = Image.open('C:\Python27\project\white-line-left.jpg') # open the Image file
        rgb_im = im.convert('RGB') #convert the image to RGB type
        width, height = rgb_im.size # get height and width of image
        pix=im.load()  # load all pixels of image in an list called "pix"
        print width, height
        
        y=int (height-(height/4)) # Height 1 to start looking for line
        r,g,b=pix[0,y]  # Get the RBG value at this heigh
        averagecolorvalue=r+g+b # Use these values to initialize the average color value at this point
        roadstarted1=0 #variable used to store the starting point of line at height 1
        # We will loop through the width of image at height 1 and get the average color value
        for x in range (0,width):
             r,g,b= pix[x,y] # rbg value of pixel
             currentcolor=r+g+b # get color value of pixel
             averagecolorvalue=(averagecolorvalue+currentcolor)/2 #Calculate Average
        # we will loop through the width again this time searching for start of line 
        for x in range (0,width):
             # We will extract r,g,b values of pixels at x, y to x,y+10    
             r,g,b= pix[x,y]      # rbg value of pixel 
             r1,g1,b1= pix[x,y+1] # rbg value of pixel 
             r2,g2,b2= pix[x,y+2] # rbg value of pixel
             r3,g3,b3= pix[x,y+3] # rbg value of pixel				
             r4,g4,b4= pix[x,y+4] # rbg value of pixel
             r5,g5,b5= pix[x,y+5] # rbg value of pixel
             r6,g6,b6= pix[x,y+6] # rbg value of pixel
             r7,g7,b7= pix[x,y+7] # rbg value of pixel
             r8,g8,b8= pix[x,y+8] # rbg value of pixel
             r9,g9,b9= pix[x,y+9] # rbg value of pixel
             r10,g10,b10= pix[x,y+10] # rbg value of pixel
             #We will now use the average value of pixels x,y to x,y+10   
             currentcolor=((r+g+b)+(r1+g1+b1)+(r2+g2+b2)+(r3+g3+b3)+(r4+g4+b4)+(r5+g5+b5)+(r6+g6+b6)+(r7+g7+b7)+(r8+g8+b8)+(r9+g9+b9)+(r10+g10+b10))/11# get average color value of pixel
             # First condition for line detection
             if (currentcolor > averagecolorvalue + 300 ):
                 #when in this if statement we will perfrom another check
                 #This time we will extract r,g,b values of pixels from x,y to x+10, y    
                 r1,g1,b1= pix[x+1,y] # rbg value of pixel
                 r2,g2,b2= pix[x+2,y] # rbg value of pixel
                 r3,g3,b3= pix[x+3,y] # rbg value of pixel
                 r4,g4,b4= pix[x+4,y] # rbg value of pixel
                 r5,g5,b5= pix[x+5,y] # rbg value of pixel
                 r6,g6,b6= pix[x+6,y] # rbg value of pixel
                 r7,g7,b7= pix[x+7,y] # rbg value of pixel
                 r8,g8,b8= pix[x+8,y] # rbg value of pixel
                 r9,g9,b9= pix[x+9,y] # rbg value of pixel
                 r10,g10,b10= pix[x+10,y] # rbg value of pixel
                 #we will calculate the average of x,y to x+1,y
                 currentcolor=((r+g+b)+(r1+g1+b1)+(r2+g2+b2)+(r3+g3+b3)+(r4+g4+b4)+(r5+g5+b5)+(r6+g6+b6)+(r7+g7+b7)+(r8+g8+b8)+(r9+g9+b9)+(r10+g10+b10))/11# get avarage color value of pixel       
                 #Second condition for line detection       
                 if (currentcolor > averagecolorvalue + 300 ):
                         #If this condition is true, we have detected a line
                         roadstarted1=x # store the x value of line
                         break # Break out of loop
        # We will now draw a red cricle at the point where we have deteced a line
        draw = ImageDraw.Draw(im)
        # The circle will help us manually verify our algorithum
        draw.ellipse((roadstarted1, y, roadstarted1+10, y+10), fill=(255, 0, 0)) # Draw a circle    
        im.save("C:\Python27\project\white-line-left.jpg","JPEG") #Save the changes to circile in a new image file
        # Now we will repeat the whole process at a different height 2
        # We will not calculate the average again but use the average calculated above
        y=int (height-(height*(0.75)))
        roadstarted2=0
        for x in range (0,width):
             r,g,b= pix[x,y] # rbg value of pixel
             r1,g1,b1= pix[x,y+1] # rbg value of pixel
             r2,g2,b2= pix[x,y+2] # rbg value of pixel
             r3,g3,b3= pix[x,y+3] # rbg value of pixel
             r4,g4,b4= pix[x,y+4] # rbg value of pixel
             r5,g5,b5= pix[x,y+5] # rbg value of pixel
             r6,g6,b6= pix[x,y+6] # rbg value of pixel
             r7,g7,b7= pix[x,y+7] # rbg value of pixel
             r8,g8,b8= pix[x,y+8] # rbg value of pixel
             r9,g9,b9= pix[x,y+9] # rbg value of pixel
             r10,g10,b10= pix[x,y+10] # rbg value of pixel
             currentcolor=((r+g+b)+(r1+g1+b1)+(r2+g2+b2)+(r3+g3+b3)+(r4+g4+b4)+(r5+g5+b5)+(r6+g6+b6)+(r7+g7+b7)+(r8+g8+b8)+(r9+g9+b9)+(r10+g10+b10))/11# get color value of pixel
             if (currentcolor > averagecolorvalue + 300 ):
                #when in this if statement we will perfrom another check
                 #This time we will extract r,g,b values of pixels from x,y to x+10, y    
                 r1,g1,b1= pix[x+1,y] # rbg value of pixel
                 r2,g2,b2= pix[x+2,y] # rbg value of pixel
                 r3,g3,b3= pix[x+3,y] # rbg value of pixel
                 r4,g4,b4= pix[x+4,y] # rbg value of pixel
                 r5,g5,b5= pix[x+5,y] # rbg value of pixel
                 r6,g6,b6= pix[x+6,y] # rbg value of pixel
                 r7,g7,b7= pix[x+7,y] # rbg value of pixel
                 r8,g8,b8= pix[x+8,y] # rbg value of pixel
                 r9,g9,b9= pix[x+9,y] # rbg value of pixel
                 r10,g10,b10= pix[x+10,y] # rbg value of pixel
                 #we will calculate the average of x,y to x+1,y
                 currentcolor=((r+g+b)+(r1+g1+b1)+(r2+g2+b2)+(r3+g3+b3)+(r4+g4+b4)+(r5+g5+b5)+(r6+g6+b6)+(r7+g7+b7)+(r8+g8+b8)+(r9+g9+b9)+(r10+g10+b10))/11# get avarage color value of pixel       
                 #Second condition for line detection       
                 if (currentcolor > averagecolorvalue + 300 ):
                         #If this condition is true, we have detected a line
                         roadstarted2=x # store the x value of line
                         break # Break out of loop
        # We will now draw a red cricle at the point where we have deteced a line
        
        draw = ImageDraw.Draw(im)
        draw.ellipse((roadstarted2, y, roadstarted2+10, y+10), fill=(255, 0, 0)) # Draw a circle    
        im.save("C:\Python27\project\white-line-left.jpg","JPEG")

        # logic to see if line is turning right 
        if ( roadstarted2 > roadstarted1 +20):
               print "turn right"
               draw.text( (width/2,height/2), "Turn Right")    
               im.save("C:\Python27\project\white-line-left.jpg","JPEG")
       #logic to see if line is turning left 
        if ( roadstarted2 < roadstarted1 -20):
               draw.text( (width/2,height/2), "Turn Left", )        
               im.save("C:\Python27\project\white-line-left.jpg","JPEG")
               print "turn left"
       #logic to see if line straight        
        if ( roadstarted2 + 19 > roadstarted1 > roadstarted2 - 20 ):
               draw.text( (width/2,height/2), "Go Straight", )  
               im.save("C:\Python27\project\white-line-left.jpg","JPEG")
               print "go straight"
processimage()
