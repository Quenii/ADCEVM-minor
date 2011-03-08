#ifndef INTELLIGER_SMART_REFERENCE_H
#define INTELLIGER_SMART_REFERENCE_H

template <class reft>
class sref
{
public:
	sref()
	{
		m_ref_count = 0;
		m_r = 0;
	}

	sref(reft* r)
	{
		m_ref_count = 0;
		m_r = r;
		inc_ref();
	}

	sref(sref& sr)
	{
		m_ref_count = 0;
		sr.inc_ref();
		inc_ref();
		m_r = sr.m_r;
	}

	~sref()
	{
		clean();
	}

	operator reft*()
	{
		return m_r;
	}
	
	reft& operator *()
	{
		if(!m_r)
		{
			throw reft();
		}
		return *m_r;
	}

	const sref& operator = (sref& sr)
	{
		sr.inc_ref();
		if(sr.m_r != m_r)
		{
			clean();
		}
		inc_ref();
		m_r = sr.m_r;
		return *this;
	}

	const sref& operator =(reft* r)
	{
		if(r != m_r)
		{
			clean();
		}
		inc_ref();
		m_r = r;
		return *this;
	}

	reft* operator->()
	{
		if(!m_r)
		{
			throw reft();
		}
		return m_r;
	}

	void* operator new(size_t s)
	{
		throw;
		return 0;
	}

protected:
	reft* m_r;
	short m_ref_count;
	
	void inc_ref(){ ++m_ref_count; }

	bool dec_ref(){ if(!(--m_ref_count)){return true;} return false; }

	virtual void clean()
	{
		if(dec_ref())
		{
			delete m_r;
			m_r = 0;
		}
	}

};

template <class reft>
class sref_a
{
public:
	sref_a()
	{
		m_ref_count = 0;
		m_length = 0;
		m_r = 0;
	}

	sref_a(reft* r, int length)
	{
		m_ref_count = 0;
		m_length = length;
		m_r = r;
		inc_ref();
	}

	sref_a(sref_a& sr)
	{
		m_ref_count = 0;
		sr.inc_ref();
		inc_ref();
		m_r = sr.m_r;
		m_length = sr.m_length;
	}
	~sref_a()
	{
		clean();
	}
	int length(){ return m_length; }

	reft& operator *()
	{
		if(!m_r)
		{
			throw reft();
		}
		return *m_r;
	}

	const sref_a& operator = (sref_a& sr)
	{
		sr.inc_ref();
		if(sr.m_r != m_r)
		{
			clean();
		}
		inc_ref();
		m_r = sr.m_r;
		m_length = sr.m_length;
		return *this;
	}

	operator reft*()
	{
		return m_r;
	}

	void* operator new(size_t s)
	{
		throw;
		return 0;
	}

protected:
	reft* m_r;
	short m_ref_count;
	int m_length;
	
	void inc_ref(){ ++m_ref_count; }

	bool dec_ref(){ if(!(--m_ref_count)){return true;} return false; }

	virtual void clean()
	{
		if(dec_ref())
		{
			delete[] m_r;
			m_r = 0;
		}
	}
};

#define I_NEW(type, args)\
	sref<type>(new type args)

#define I_NEWA(type, count)\
	sref_a<type>(new type[count], count)

#endif
// INTELLIGER_SMART_REFERENCE_H