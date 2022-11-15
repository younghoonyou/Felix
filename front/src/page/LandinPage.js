import React, { useState } from 'react';
import axios from 'axios';
import '../App.css'
import InputName from '../components/InputName';
import NumberBox from '../components/NumberBox';
import ConfirmButton from '../components/ConfirmButton';
import Amount from '../components/Amount';
const LandingPage = () => {
  const [user, setUser] = useState('');
  const [restaurant, setRestaurant] = useState('');
  const [amount, setAmount] = useState('');
  const config = {
    headers: {
      'Content-Type': 'application/json',
    },
  };
    const Fetch = async (user,restaurant,amount) => {
        const ret = await axios.post(
          'http://127.0.0.1:8888',
          { user,restaurant,amount},
          config
        );
    }
  const handleSubmit = async(e) => {
    e.preventDefault();
    Fetch(user,restaurant,amount);
  }
  return (
    <div className='Rectangle-Box'>
      <form className='Form-Box' onSubmit={handleSubmit}>
        <InputName
          title='User'
          value={user}
          onChange={(e) => setUser(e.target.value)}
          pre={'User Name'}
        />
        <InputName
          title='Restaurant'
          value={restaurant}
          onChange={(e) => setRestaurant(e.target.value)}
          pre={'Restaurant Name'}
        />
        <Amount amount={amount} />
        <NumberBox amount={setAmount} total={amount} />
        <ConfirmButton title='Confirm amount' />
      </form>
    </div>
  );
};

export default LandingPage;
