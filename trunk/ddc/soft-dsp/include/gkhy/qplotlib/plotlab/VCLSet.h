// VCLSet.h
//
//    INNOVATIVE INTEGRATION CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or nondisclosure 
//  agreement with Innovative Integration Corporation and may not be copied or 
//  disclosed except in accordance with the terms of that agreement.
//  Copyright (c) 2000..2005 Innovative Integration Corporation. 
//  All Rights Reserved.
//

#ifndef VCLSetH
#define VCLSetH

//=============================================================================
//  CLASS CTSet  --
//=============================================================================
template<class T, unsigned char minEl, unsigned char maxEl>
class CTSet
{
protected:
//    unsigned char Data[((((int)(maxEl/8))-((int)(minEl/8))+1) != 3)?
//         (((int)(maxEl/8))-((int)(minEl/8))+1): 4];

	unsigned char Data[ 4 ];

public:
	operator int() const { *((int *)Data ); }
	CTSet<T, minEl, maxEl> operator = ( int value ) { *((int *)Data ) = value; return *this; }

public:
    CTSet() { memset(Data, 0, sizeof (Data)); }
	CTSet( int value )
	{
		*((int *)Data ) = value;
	}

    CTSet(const CTSet& src)
      {
      for (int i = 0; i < sizeof (Data); i++)
        Data[i] = src.Data[i];
      }

    CTSet& operator =(const CTSet& rhs)
      {
      if (this != &rhs)
        {
        for (int i = 0; i < sizeof (Data); i++)
        Data[i] = rhs.Data[i];
        }
        
      return *this;
      }
      
    CTSet& operator +=(const CTSet& rhs)     //Union
      {
      for (int i = 0; i < sizeof (Data); i++)
        Data[i] |= rhs.Data[i];
      return *this;
      }
      
    CTSet&  operator -=( const CTSet& rhs )     //Difference
      {
      for (int i = 0; i < sizeof (Data); i++)
        Data[i] ^= (Data[i] & rhs.Data[i]);
        
      return *this;
      }

    CTSet&  operator *=( const CTSet& rhs )     //Intersection
      {
      for (int i = 0; i < sizeof (Data); i++)
        Data[i] &= rhs.Data[i];
      return *this;
      }

    CTSet  operator +( const CTSet& rhs ) const //Union
      {
      CTSet<T, minEl, maxEl> s;
      for (int i = 0; i < sizeof (Data); i++)
        s.Data[i] = Data[i] | rhs.Data[i];
        
      return s;
      }

    CTSet  operator -( const CTSet& rhs ) const //Difference
      {
      CTSet<T, minEl, maxEl> s;
      for (int i = 0; i < sizeof (Data); i++)
        s.Data[i] = Data[i] ^ (Data[i] & rhs.Data[i]);
        
      return s;
      }

    CTSet  operator *( const CTSet& rhs ) const //Intersection
      {
      CTSet<T, minEl, maxEl> s;
      for (int i = 0; i < sizeof (Data); i++)
        s.Data[i] = Data[i] & rhs.Data[i];

      return s;
      }

    CTSet&  operator <<( const T el ) //Add element
      {
      if (el >= minEl && el <= maxEl)
        Data[(int)(el/8) - (int)(minEl/8)] |=
        (unsigned char)((unsigned short)1 << (el % 8));
      return *this;
      }
      
    CTSet&  operator >>( const T el ) //Remove element
      {
      if (el >= minEl && el <= maxEl)
        Data[(int)(el/8) - (int)(minEl/8)] &=
        (unsigned char)~((unsigned short)1 << (el % 8));
        
      return *this;
      }

    bool  Contains(const T el) const
      {
      return (el >= minEl && el <= maxEl)?
        (Data[(int)(el/8) - (int)(minEl/8)] & (unsigned char)((unsigned short)1 << (el % 8))) :
        false;
      }

    CTSet&  Clear()
      {
      memset(Data, 0, sizeof (Data));
      return *this;
      }

    bool  Empty() const
      {
      for (int i = (sizeof(Data) >> 1)-1; i >= 0; --i)
        if (((short *) Data)[i] != 0)
          return false;
      if (sizeof(Data) & 1)
        return (Data[sizeof(Data)-1] == 0);
        
      return true;
      }

    bool  operator ==(const CTSet& rhs) const
      {
      for (int i = 0; i < sizeof (Data); i++)
        if (Data[i] != rhs.Data[i])
        // Not so fast, if first or last byte, make sure that
        // the compare does not include unused bits (mask them)
        if (i == 0)
          {
          if (((0xFF >> (8-(minEl%8))) ^ Data[i]) !=
          ((0xFF >> (8-(minEl%8))) ^ rhs.Data[i]))
          return false;
          }

        else if (sizeof (Data) > 1 && i == sizeof (Data) - 1)
          {
          if (((0xFF << (1+(maxEl%8))) ^ Data[i]) !=
          ((0xFF << (1+(maxEl%8))) ^ rhs.Data[i]))
          return false;
          }

        else
          return false;
          
      return true;
      }
      
    bool  operator !=(const CTSet& rhs) const {return !operator==(rhs);}
};
//---------------------------------------------------------------------------
#endif