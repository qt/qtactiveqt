TEMPLATE = subdirs

CONFIG	+= ordered
SUBDIRS	= axshared.pro container
!wince*: SUBDIRS += control

