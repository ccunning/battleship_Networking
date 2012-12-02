battleship_Networking
=====================

When you win: "All your ships are belong to us"

When you hit: "BOOM, sucka"

When you sink a ship: "You been done got sinked, bro"

When you miss: "Dude, phailure..."

-------------------

First:

  ssh-add -l

see if anything comes up. If nothing comes up, do

  ssh-keygen -t rsa
  
It will ask you for a location, just press enter

Then,run the 'ssh-add -l' command again and you should see something.

Change your directory to ~/.ssh/ and you should see a file called id_rsa.pub. Copy the contents of the file and go to github.com.
Go to account settings in the top right corner, and navigate to SSH Keys on the left side. Click 'New SSH Key' and paste the key that you copied from
the id_rsa.pub file. Add a title and add key.

Then, go to the repository and get the url for the ssh connection. Just use that instead of any https connections.

That should be it.

-----------------

Commands

Start of Turn - (0,0,0)

Fire - (1,Loc1,Loc2)

End of turn - (2,0,0)

ACK - (7,0,0)

Ready - (8,0,0)

Quit - (9,0,0)